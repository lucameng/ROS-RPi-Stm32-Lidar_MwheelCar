#include "CarCmd.h"

TCMD_HEX CMD;
int id;

void Car_MoveAsStatus(Car_Status status,UART_HandleTypeDef* huartp)
{
	id=1;
	while(id<=4) 
	{
		CMD=StatusToCMD(status,id);
		HAL_UART_Transmit_DMA(huartp,(uint8_t *)&CMD,sizeof(CMD));
		HAL_Delay(10);
		id++;
	}
}

void Car_Stop(UART_HandleTypeDef* huartp)
{
	id=1;
	while(id<=4) 
	{
		CMD=Stop_CMD(id);
		HAL_UART_Transmit_DMA(huartp,(uint8_t *)&CMD,sizeof(CMD));
		HAL_Delay(10);
		id++;
	}
}

void Car_Init(UART_HandleTypeDef* huartp)
{
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
	
	id=1;
	while(id<=4) 
	{
		CMD=Enable_CMD(id);
		HAL_UART_Transmit_DMA(huartp,(uint8_t *)&CMD,sizeof(CMD));
		HAL_Delay(10);
		id++;
	}
}