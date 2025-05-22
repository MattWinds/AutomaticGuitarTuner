# AutomaticGuitarTuner

This project was done in my third year Control Systems class with my classmate Carolina.

The overall objective of this project was to create an automated guitar tuner by measuring the frequency of a string, comparing that frequency to a set point, and using a form of PID controller to get the input equal to the set point. Based on the comparison between the input and set point, the motor will turn in the appropriate direction until the frequency measured matches the setpoint. This was done using an Arduino Uno, a Bojack L298N motor driver, a 4.8V motor which was taken from a WARRIOR 4.8V cordless screwdriver, a Scarlett Audio Interface, MATLAB, and the Arduino software. A bang-bang controller was initially designed, which was developed into a P controller.

Attached are 4 files:
ELEC_3355_FINAL_ARDUINO: Arduino File
ELEC_3355_FINAL_MATLAB: Matlab File
ControlSystemsData.xlsx: Measured Data in Excel format
ELEC3355_REPORT_WINDSOR_DELACRUZ: PDF report 
