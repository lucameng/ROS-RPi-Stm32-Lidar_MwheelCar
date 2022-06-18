#ifndef __SOMEFILE_P_

#define __SOMEFILE_P_

#include "stdint.h"
#include "main.h"
#include "CarStatus.h"

typedef	union{
		float fv;
		uint8_t cv[4];
}float_union;

//接收数据结构
typedef	struct{

		float_union		linear_vx;//线速度x
		float_union		linear_vy;//线速度y
		float_union		angular_v;//角速度
		
}rcv_data;

typedef __packed struct
{
	uint8_t Header;
	uint8_t Enable;
	double Vy;            //纵向
	double Vx;            //横向 
	double Spin;
}PCcmd;


void CMDReceive(Car_Status* CMDToSTM,UART_HandleTypeDef*);

#endif