#include "power.h"

void DeepSleep(){
	/* Pre sleep housekeeping */
	PrintToConsole("Sleep button pressed, Unplug from USB. Zzzzzz.....\0");
	//USB transmission is interrupt based, wait 10 milliseconds for it to transfer before killing it
	HAL_Delay(10);
	//In the future, shut off the LED matrix and LEDs here

	// Chip goes to sleep here, waits for interrupt
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFE);
	//Chip wakes up here

	/* Post wakeup housekeeping */
	SystemClock_Config();
	stopState = 0;
}
