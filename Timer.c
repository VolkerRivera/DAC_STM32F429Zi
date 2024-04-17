#include "cmsis_os2.h"                          // CMSIS RTOS header file


osTimerId_t timeout1;                            // timer id

static uint32_t exec1;                          // argument for the timer call back function

// One-Shoot Timer Function
static void CallbackTimeout1 (void const *arg) {
  // add user code here

}
 
 
// Example: Create and Start timers
int Init_Timers (void) {
  //osStatus_t status;                            // function return status
 
  // Create one-shoot timer
  exec1 = 1U;
  timeout1 = osTimerNew((osTimerFunc_t)&CallbackTimeout1, osTimerOnce, &exec1, NULL); //Se crea un timeout pero aun no se le asigna tiempo
 
  return NULL;
}
