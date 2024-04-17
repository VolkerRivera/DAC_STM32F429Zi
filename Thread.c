#include "cmsis_os2.h"                          // CMSIS RTOS header file
 
/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
osThreadId_t tid_Thread;                        // thread id
extern osTimerId_t tim_id1;
extern int Init_Timers (void);
extern void melodiaEntrar(void);
 
void Thread (void *argument);                   // thread function
 
int Init_Thread (void) {
 
  tid_Thread = osThreadNew(Thread, NULL, NULL);
  if (tid_Thread == NULL) {
    return(-1);
  }
 
  return(0);
}
 
void Thread (void *argument) {
	
	Init_Timers();

  while (1) {
    ; // Insert thread code here...
		osThreadFlagsWait(0x01, osFlagsWaitAny, osWaitForever);
//		osTimerStart(tim_id1, 250);
		melodiaEntrar();
//		cambiaTono(100, 1000);
		//osDelay(1000);
    osThreadYield();                            // suspend thread
  }
}
