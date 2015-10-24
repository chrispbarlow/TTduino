TTduino
=======

Time Triggered scheduler example for Arduino

Note: if you're looking for the scheduler logic, it has now been moved to http://github.com/chrispbarlow/libTTduino

This project now serves as an example of how to use the library.

This is an implementation of a Time Triggered Cooperative (TTC) schedule, based on the designs by Dr Michael J. Pont (see http://www.safetty.net/training/beginners)

The project is built in Eclipse Juno (http://www.eclipse.org/downloads/packages/eclipse-ide-cc-developers/junosr2) 
using the Arduino for Eclipse plugin, developed by Jan Baeyens (see http://eclipse.baeyens.it/Install.shtml for installation instructions)

Task x has 2 functions:

x_Init() is called once from the familiar Arduino setup() function.

x_update() is called periodically, as prescribed in the task array in TTduino.cpp.

