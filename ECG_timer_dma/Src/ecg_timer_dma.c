/*
 * ecg_timer_dma.c
 *
 *  Created on: Jun 19, 2025
 *      Author: ADMIN
 */


#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include <stdio.h>
#include "ecg_timer_dma.h"

uint16_t adc_buffer[DMA_BUFFER_LEN];
char uart_buf[64];


void ad8232_timer_dma_task(ADC_HandleTypeDef *_hadc, TIM_HandleTypeDef *htim){
	HAL_TIM_Base_Start(&htim2); //Start Timer (de kich hoat ADC qua TRGO)

	//Start ADC voi DMA, doc DMA_BUFFER_LEN mau
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_buffer, DMA_BUFFER_LEN);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc){
	if(hadc->Instance == ADC1){
		for(int i = 0; i < DMA_BUFFER_LEN; i++){
			int len = sprintf(uart_buf, "%u\r\n", adc_buffer[i]);
			HAL_UART_Transmit(&huart1, (uint8_t*)uart_buf, len, HAL_MAX_DELAY);
		}
	}
}

#ifdef __cplusplus
}
#endif
