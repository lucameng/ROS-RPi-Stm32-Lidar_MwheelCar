#ifndef __SOMEFILE_CarCmd__   
 
#define __SOMEFILE_CarCmd__   


#include "main.h"
#include "CarStatus.h"

void Car_MoveAsStatus(Car_Status status,UART_HandleTypeDef*);
void Car_Stop(UART_HandleTypeDef* );

void Car_Init(UART_HandleTypeDef*);

#endif   