#ifndef __ECG_TIMER_DMA_H_
#define __ECG_TIMER_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdio.h>

#define DMA_BUFFER_LEN 100

extern uint16_t adc_buffer[DMA_BUFFER_LEN];
extern char uart_buf[64];

extern TIM_HandleTypeDef htim2;
extern ADC_HandleTypeDef hadc1;
extern UART_HandleTypeDef huart1;

void ad8232_timer_dma_task(ADC_HandleTypeDef *_hadc, TIM_HandleTypeDef *htim);

//Ham callback khi DMA doc xong 1 vong buffer
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);

#ifdef __cplusplus
}
#endif

#endif //__ECG_TIMER_DMA_H
