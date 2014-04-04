// Do not remove the include below
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include "TTduino.h"


/*
 * Define how often the ticks occur, and the number of tasks in the schedule
 */
#define TICK_PERIOD (1000) 	/* Tick period in microseconds */
#define NUM_TASKS 	(4)		/* Total number of tasks */

bool schedLock = false;

/*
 * The task array.
 * This dictates the tasks to be run from the scheduler
 * The order of these tasks sets their priority, should more than one task run in one tick
 * */
task_t Tasks[NUM_TASKS] =
{
	{
		blink_update,
		10,
		0
	},

	{
		exampleTask1_update,
		10,
		1
	},

	{
		exampleTask2_update,
		10,
		2
	},

	{
		exampleTask3_update,
		10,
		3
	}

};

/*
 * The familiar Arduino setup() function: runs once when you press reset.
 * x_Init() functions contain initialisation code for the related tasks.
 */
void setup()
{
	wdt_disable();			/* Disable the watchdog timer */

	blink_Init();
	exampleTask1_Init();
	exampleTask2_Init();
	exampleTask3_Init();

	tick_Start();
}

/*
 * Start the timer interrupts
 */
void tick_Start()
{
	/* initialize Timer1 */
	cli(); 			/* disable global interrupts */
	TCCR1A = 0; 	/* set entire TCCR1A register to 0 */
	TCCR1B = 0; 	/* same for TCCR1B */

	/* set compare match register to desired timer count: */
	OCR1A = (16 * TICK_PERIOD); /* TICK_PERIOD is in microseconds */
	/* turn on CTC mode: */
	TCCR1B |= (1 << WGM12);
	/* enable timer compare interrupt: */
	TIMSK1 |= (1 << OCIE1A);
	TCCR1B |= (1 << CS10);
	sei(); /* enable global interrupts (start the timer)*/
}


/*
 * The ISR runs periodically every TICK_PERIOD
 */
ISR(TIMER1_COMPA_vect)
{

	sleep_disable();        /* disable sleep */
	power_all_enable();		/* restore all power */
	schedLock = false;		/* allow scheduler to run */

}

/* The loop function handles scheduling of the tasks */
void loop()
{
	uint8_t i;
	sleepNow();															/* Go to sleep. Woken by ISR loop continues, then sleep repeats */

/******************** Nothing happens until interrupt tick *****************************************/
	if (schedLock == false)												/*schedLock prevents scheduler from running on non-timer interrupt */
	{
		for(i = 0; i < NUM_TASKS; i++)									/* For every task in schedule */
		{
			if(Tasks[i].task_delay == 0)								/* Task is ready when task_delay = 0 */
			{
				Tasks[i].task_delay = (Tasks[i].task_period - 1);		/* Reload task_delay */
				(*Tasks[i].task_function)();							/* Call task function */
			}
			else
			{
				Tasks[i].task_delay--;									/* task delay decremented until it reaches zero (time to run) */
			}
		}
	}
}


void sleepNow()
{

	set_sleep_mode(SLEEP_MODE_IDLE);  									/* sleep mode is set here */

	sleep_enable();														/* enables the sleep bit in the mcucr register */
																		/* so sleep is possible. just a safety pin */

	power_adc_disable();												/* Power down some things to save power */
	power_spi_disable();
	power_timer0_disable();
	power_twi_disable();

	schedLock = true;													/* Prevent schedule from running on accidental wake-up */
	sleep_mode();            											/* here the device is actually put to sleep!! */
																		/* THE PROGRAM IS WOKEN BY TIMER1 ISR */
}
