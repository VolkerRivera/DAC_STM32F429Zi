#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "math.h"
#include "dac.h"
#include "dma.h"
#include "tim.h"
 
/*----------------------------------------------------------------------------
 *      Timer: Sample timer functions
 *---------------------------------------------------------------------------*/

extern DAC_HandleTypeDef hdac;
extern DMA_HandleTypeDef hdma_dac1;
extern TIM_HandleTypeDef htim2;
extern uint32_t sine_val[100];
extern void sinusoide(void);

int periodos[10]={1, 2, 4, 5, 8, 10, 20, 30, 40, 50};

void cambiaTono(int period, int delay){
	
	
	HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1);
	HAL_TIM_Base_Stop(&htim2);
	htim2.Init.Period = period;
	HAL_TIM_Base_Init(&htim2);
	HAL_TIM_Base_Start(&htim2);
	sinusoide();
	HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, sine_val, 100, DAC_ALIGN_12B_R);
	osDelay(delay);
	
	
}

void melodiaEntrar(void){
	cambiaTono(20,1000);
	cambiaTono(40,250);
	cambiaTono(20,250);
//	cambiaTono(40,1000);
	//cambiaTono(100,500);
	cambiaTono(10,1000);
//	osDelay(100);
	HAL_TIM_Base_Stop(&htim2);
}
/*----- One-Shoot Timer Example -----*/
osTimerId_t tim_id1;                            // timer id
static uint32_t exec1;                          // argument for the timer call back function

int j = 0;
// One-Shoot Timer Function
static void Timer1_Callback (void const *arg) {
  // add user code here
	//cambiaTono(periodos[j]);
	if(j<10){
		j++;
	}else{
		j=0;
	}
}
 
 
// Example: Create and Start timers
int Init_Timers (void) {
  //osStatus_t status;                            // function return status
 
  // Create one-shoot timer
  exec1 = 1U;
  tim_id1 = osTimerNew((osTimerFunc_t)&Timer1_Callback, osTimerOnce, &exec1, NULL);
//  if (tim_id1 != NULL) {  // One-shot timer created
//    // start timer with delay 100ms
//    status = osTimerStart(tim_id1, 100U); 
//    if (status != osOK) {
//      return -1;
//    }
//  }
 
  return NULL;
}
