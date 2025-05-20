# ENCE361 Step Counter Project

This project implements a step counter on the STM32 Nucleo-64 Development Board, based on the Arm® Cortex®-M0+ microprocessor. This is combined with the University of Canterbury RCAP expansion board, featuring an OLED display, joystick, buttons, buzzer, potentiometer and inertial measurement unit, all of which are used to implement the step counter.

The following operation modes are included:
- A step count state, displaying the number of steps taken as an integer or percentage of the current step goal, since last reset.
- A distance state, displaying an approximation of distance travelled (in kilometres or yards).
- A goal state, allowing the user to see their current goal, the percentage of the goal that has been completed.
- A goal modification state, allowing the user to set a step goal (between 500 and 15000) using the potentiometer.
- A test state, allowing a developer to manually set the current step count for debugging purposes.

These states are summarised by the FSM diagram below.
![FSM](fsm.png)

Some additional features include:
- Alerts via the buzzer upon goal completion.
- LED Indicators for visual indication of goal completion.

## Modularisation
### Description
![Block Diagram](block-diagram.png)

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
Plot of raw data (x,y,z), plot of filtered data(x,y,z), plot of magnitude, plot containing hysteresis regions (red blocks showing when in hysteresis). Description of how we picked upper and lower hysteresis values. Description of level-surface rejection. 

### Scheduler Description
How our design is interrupt-driven. How our task scheduling works. 

### Scheduler Timing
Task schedule diagram. Justification of each refresh rate. Address the problem of having back-to-back tasks, comment on why it won't impact performance here.

## Conclusion
What we learnt, what went well, problems we faced, things to improve on in the future.