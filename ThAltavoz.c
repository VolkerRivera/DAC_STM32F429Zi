#include "cmsis_os2.h"                          // CMSIS RTOS header file
#include "tim.h"
#include "math.h"
#include "dac.h"
#include "dma.h"

/* BELONG TO THIS THREAD */
osThreadId_t tid_ThreadAltavoz; //TREAD ALTAVOZ ID
void FuncionThreadAltavoz (void *argument);// thread function
void cambiaTono(int period); // saca una onda sinusoidal indefinidamente hasta que se vuelva a llamar a la funcion
 
/* FROM DAC */
extern DAC_HandleTypeDef hdac;

/* FROM DMA */
extern DMA_HandleTypeDef hdma_dac1;

/* FROM TIM */
extern TIM_HandleTypeDef htim2;

uint32_t sine_val[100];
#define PI 3.1415926

void sinusoide(void){ //Da valor a 100 puntos de una onda sinusoidal
	int i;
	for(i = 0; i < 100; i++){
		sine_val[i]=((sin(i*2*PI/100)+1)*(4096/2));
	}
}

void cambiaTono(int period){

	HAL_DAC_Stop_DMA(&hdac, DAC_CHANNEL_1); // Para DMA 
	HAL_TIM_Base_Stop(&htim2); // y TIMER antes de cambiar periodo
	htim2.Init.Period = period; // Cambia periodo
	HAL_TIM_Base_Init(&htim2); //Inicializa el tim2 con su nuevo periodo
	HAL_TIM_Base_Start(&htim2); //Inicia la cuenta de tim2
	sinusoide(); //crea los 100 valores de la onda sinusoidal a representar
	HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, sine_val, 100, DAC_ALIGN_12B_R); //mete dicha onda y la convierte a analog
	
}

 
int Init_ThreadAltavoz (void) {
 
  tid_ThreadAltavoz = osThreadNew(FuncionThreadAltavoz, NULL, NULL);
  if (tid_ThreadAltavoz == NULL) {
    return(-1);
  }
 
  return(0);
}
 
void FuncionThreadAltavoz (void *argument) {

  while (1) {
    //Dependiendo de la flag suena un tono u otro
		osThreadFlagsWait(FLAG_THALTAVOZ, osFlagsWaitAny, osWaitForever); //Espera flag enviado desde la interrupcion del boton azul
		cambiaTono(20);
    osDelay(1000);
    cambiaTono(40);
    osDelay(250);
    cambiaTono(20);
    osDelay(250);
    cambiaTono(10);
    osDelay(1000);
    HAL_TIM_Base_Stop(&htim2);
    osThreadYield();                            // suspend thread
  }
}
