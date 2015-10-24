// Do not remove the include below
#include "main.h"
#include "libTTduino/libTTduino.h"

/*
 * Task includes
 * These header files contain the function prototypes for your tasks
 * */
#include "Tasks/Blink/Blink.h"
#include "Tasks/exampleTask1/exampleTask1.h"
#include "Tasks/exampleTask2/exampleTask2.h"
#include "Tasks/exampleTask3/exampleTask3.h"

/*
 * The familiar Arduino setup() function: runs once when you press reset.
 * x_Init() functions contain initialisation code for the related tasks.
 */
void setup(){
	TTduino_addTask(blink_Init, blink_update, 10, 0);
	TTduino_addTask(exampleTask1_Init, exampleTask1_update, 10, 1);
	TTduino_addTask(exampleTask2_Init, exampleTask2_update, 10, 2);
	TTduino_addTask(exampleTask3_Init, exampleTask3_update, 10, 3);

	TTduino_start(1000);
	/* NOTE: with the current settings, the maximum value for this can be 4095 microseconds without changing the timer prescalar */
}

/* The loop function handles scheduling of the tasks */
void loop(){
	TTduino_runScheduledTasks();
}
