// Only modify this file to include
// - function definitions (prototypes)
// - include files
// - extern variable definitions
// In the appropriate section

#ifndef _TTduino_H_
#define _TTduino_H_
#include "Arduino.h"

/*
 * Task includes
 * These header files contain the function prototypes for your tasks
 * */
#include "Tasks/Blink/Blink.h"
#include "Tasks/exampleTask1/exampleTask1.h"
#include "Tasks/exampleTask2/exampleTask2.h"
#include "Tasks/exampleTask3/exampleTask3.h"

/* Standard Arduino stuff */
#ifdef __cplusplus
extern "C" {
#endif
void loop();
void setup();
#ifdef __cplusplus
} // extern "C"
#endif


/*
 * Function pointer for task array
 * This links the Task list with the functions from the includes
 * */
typedef volatile void (*task_function_t)(void);

/* Task properties */
typedef struct
{
	task_function_t task_function;	/* function pointer */
	uint32_t        task_period;	/* period in ticks */
	uint32_t        task_delay;		/* initial offset in ticks */
} task_t;


// Prototypes
void tick_Start(void);
void sleepNow(void);

//Do not add code below this line
#endif /* _TTduino_H_ */
