# ENCE361 Step Counter Project

This project implements a step counter on the STM32 Nucleo-64 Development Board, based on the Arm® Cortex®-M0+ microprocessor. This is combined with the University of Canterbury RCAP expansion board, featuring an OLED display, joystick, buttons, buzzer, potentiometer and intertial measurement unit, all of which are used to implement the step counter.

The following operation modes are included:
- A step count state, displaying the number of steps taken as an integer or percentage of the current step goal, since last reset.
- A distance state, displaying an approximation of distance travelled (in kilometers or yards).
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
This section should be brief. Explanation of application layer, driver layer. Description of types of modules (kernel module, task modules, shared data modules).

### Justification
Why we used the layered approach. Why each task has a module. Why the FSM task was split into sub-tasks. Why the IMU filtering was done externally to the IMU module. Why the step / goal counts were seperated from the FSM / Display. Why adc_controller.h is seperate from pot.h and joystick.h. 

## Firmware Operation

### IMU Processing
Plot of raw data, plot of filtered data, plot containing hysteresis regions. Description of how we picked upper and lower hysteresis values. Description of level-surface rejection. 

### Scheduller Description
How our design is interrupt-driven. How our task schedulling works. 

### Scheduller Timing
Task schedule diagram. Justification of each refresh rate. Address the problem of having back-to-back tasks, comment on why it won't impact performance here.

## Conclusion
What we learnt, what went well, problems we faced, things to improve on in the future.