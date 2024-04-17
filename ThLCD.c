#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "lcd.h"
#include "main.h"
 
osThreadId_t tid_ThLCD;                        // thread id
 
void ThreadLCDFunction (void *argument);                   // thread function
 
int Init_ThreadLCD (void) {
 
  tid_ThLCD = osThreadNew(ThreadLCDFunction, NULL, NULL);
  if (tid_ThLCD == NULL) {
    return(-1);
  }
 
  return(0);
}
 
void ThreadLCDFunction (void *argument) {
  uint8_t contador = 0;
  char msg[30];
  
  while (1) {
    // Insert thread code here...
    erase_screen();
    sprintf(msg,"%d",contador);
    write(1,msg);
    write(2,"eooeoeoeo");
    contador++;
    osDelay(1000);
    osThreadYield();                            // suspend thread
  }
}
