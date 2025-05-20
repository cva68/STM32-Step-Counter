# ENCE361 Step Counter Project

This project implements a step counter on the STM32 Nucleo-64 Development Board, based on the Arm® Cortex®-M0+ microprocessor. This is combined with the University of Canterbury RCAP expansion board, featuring an OLED display, joystick, buttons, buzzer, potentiometer and inertial measurement unit, all of which are used to implement the step counter.

The following operation modes are included:
- A step count state, displaying the number of steps taken as an integer or percentage of the current step goal, since last reset.
- A distance state, displaying an approximation of distance travelled (in kilometres or yards).
- A goal state, allowing the user to see their current goal, the percentage of the goal that has been completed.
- A goal modification state, allowing the user to set a step goal (between 500 and 15000) using the potentiometer.
- A test state, allowing a developer to manually set the current step count for debugging purposes.

These states are summarised by the FSM diagram below.
![FSM](./Documentation%20Images/fsm.png)

Some additional features include:
- Alerts via the buzzer upon goal completion.
- LED Indicators for visual indication of goal completion.

## Modularisation
### Description
![Block Diagram](./Documentation%20Images/block-diagram.png)

The modules were split into three different sections:
- Hardware Abstraction Layer: Inbuilt / provided modules to interface with peripherals
- Driver Layer: Further abstraction from the hardware layer, providing simple functions to perform common actions on peripherals.
- Application Layer: The kernel and the task modules, with supporting modules.

Each task had its own module, prefixed with `task_`, indicated in purple on the above diagram. These tasks often shared data sources; for example, joystick values or step count. These shared data modules
are indicated in green.

Some modules in the above diagram were builtins from STM32, or provided by the university - these are indicated in orange.

### Justification
The first consideration when modularising this code was separability. Particularly for modules on the driver layer,
it was vital that the modules could be reused in multiple places. For example, the `joystick` module is used by multiple
tasks, so it had to be designed in a fashion that made it provide data that was useful for a range of purposes. In this
case, this meant providing multiple forms of data as outputs, being percentage displacements and boolean flags for directions.
Not only did this simplify interacting with the joystick for this particular project, but it allows easy reusability for other
similar configurations in future projects, particularly because the module was designed to have minimal dependency on other modules.
This same theory was applied to all the other modules on the driver layer.

This ties into a second key aspect considered in our design, rigidity. To avoid having to change many parts of the code to
implement a single behaviour change, modules were designed to have a single purpose, and repetitions of behaviour were avoided. A key example of this is the `steps` module. If the step count and current goal were to be stored in many different modules, changing the behaviour of the step count or goal would require modifying many different files (such as `state_goal`, `state_test` and `state_count`). Now, if a change needed to be made to the way steps were incremented or the goal is stored (e.g. changing the size of the step count variable), this would only need to happen in a single place. 

In turn, this rigidity also decreased fragility. Having well-defined behaviours for each module resulted in decreased coupling between modules, hence preventing different behaviours from clashing in unexpected ways. This was the primary reason for separating the `pot` and `joystick` modules, having one central `adc_controller` module that they pull data from. Hence, changing the behaviour of the potentiometer is guaranteed to have no impact on the joystick, which would not be the case if `adc_controller` had abstraction for the potentiometer and joystick built-in.

Some modularisation choices were made purely for maintaining separation of concerns, such as the `state_` modules being separated from the FSM, and the `filter` module being separated from the `imu` driver. In the case of the `state_` modules, isolating the individual state behaviours from the FSM made it much clearer what each state does, and much clearer how the FSM switches through states. For the `filter` module, the functionality was very much different from the `imu` driver itself, hence separating them was logical for maintaining cohesion. This separation of concerns greatly improves readability.

Overall, the choices for modularisation have reduced rigidity and fragility, and improved separability and readability. This allows for easy modification of the project, and re-use of the modules for other projects.


## Firmware Operation

### IMU Processing
A key consideration when developing the IMU module was calibration abstraction. Raw values from the IMU sensor are not inherently consistent or accurate due to hardware imperfections so a offset and scale system were introduced to average output across all three axes. This calibration layer was implemented as part of the driver itself to ensure that all data accessed through the module is already normalised, improving reliability and removing the need for external correction logic.

![Raw Sensor Data](./Documentation%20Images/raw_sensor.png)

Once the IMU data has been read it is passed through a filtering process to reduce noise and produce more stable readings. This is achieved using a moving average filter implemented as a circular buffer. Each axis of the IMU has its own dedicated filter instance, which stores a fixed number of recent samples. When a new acceleration value is received, it replaces the oldest value in the buffer, and the filtered output is computed as the average of all values in the buffer. By filtering at this stage, we ensure that any logic using IMU values relies on consistent and predictable input.

![Filtered Sensor Data](./Documentation%20Images/filtered_sensor.png)

To determine when a step occurs, we calculate the acceleration magnitude using the filtered X, Y, and Z axis values. This provides a measure of motion intensity that is independent from direction, which is particularly useful for detecting steps in any orientation. To improve reliability, we implemented a hysteresis approach with clearly defined upper and lower bounds. The upper threshold is chosen to capture the distinct spike in acceleration caused by a step, while the lower threshold ensures that small fluctuations or noise do not repeatedly trigger step events. This separation prevents rapid toggling and stabilises step detection. In addition to hysteresis, we also introduced a level-surface rejection mechanism by monitoring the Z-axis acceleration. If the Z-axis reading remains within a narrow range around 1G—the expected acceleration when stationary on a flat surface—then step detection is suppressed. This helps avoid false positives when the device is idle but still subject to minor vibrations or tilt. So that only deliberate movement is detected.

![Magnitude Data](./Documentation%20Images/mag_sensor.png)

### Scheduler Description
Our design is fundamentally interrupt-driven, built around the use of the HAL_GetTick() function. Which is updated via the SysTick timer interrupt at a 1 kHz frequency. This tick-based mechanism allows us to implement a cooperative task scheduler that executes tasks at precise intervals without relying on blocking delays. Each task in the system is associated with a specific frequency that is converted to tick periods. In the main loop, the current tick count is compared against the scheduled run times of each task, and when a task is due, it is executed and its next run time is updated. This structure ensures time-sensitive tasks are serviced regularly while less critical tasks run at lower frequencies to conserve CPU resources. Because all timing is driven by the SysTick interrupt, we achieve consistent scheduling with minimal jitter. Additonally, it makes our task management remains easy to modify or add new modules.

### Scheduler Timing
Task schedule diagram. Justification of each refresh rate. Address the problem of having back-to-back tasks, comment on why it won't impact performance here.

![Task Schedule Diagram](./Documentation%20Images/task_schedule.png)

### Task Refresh Rate Justification

- **Button Task (100 Hz):**  
  Ensures responsive input handling and reliable debouncing without delay.

- **Joystick Task (10 Hz):**  
  Captures user input at a moderate frequency for smooth control without excessive sampling.

- **ADC Task (10 Hz):**  
  Samples analog inputs at a sufficient rate for typical usage while minimizing system load.

- **FSM Task (6 Hz):**  
  Updates the display state machine slowly enough to reduce flicker, yet fast enough to remain responsive.

- **Buzzer Task (6 Hz):**  
  Controls audio output with moderate timing resolution for alert patterns or tones.

- **LED Task (6 Hz):**  
  Updates LED indicators with perceptually smooth transitions and status changes.

- **IMU Task (50 Hz):**  
  Provides high enough frequency to accurately detect steps and motion while avoiding unnecessary CPU usage.

A potential issue with this scheduling is back-to-back task execution where multiple tasks may become ready to execute in the same tick... Idk why it wont affect preformance :|

## Conclusion
What we learnt, what went well, problems we faced, things to improve on in the future.

Man idk the ENCE361-25S1 - Embedded Systems 1 grade was the friends we made along the way.