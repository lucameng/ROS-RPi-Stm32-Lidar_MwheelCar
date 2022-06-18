#ifndef __SOMEFILE_P_

#define __SOMEFILE_P_

#include "stdint.h"
#include "main.h"
#include "CarStatus.h"

typedef	union{
		float fv;
		uint8_t cv[4];
}float_union;

//�������ݽṹ
typedef	struct{

		float_union		linear_vx;//���ٶ�x
		float_union		linear_vy;//���ٶ�y
		float_union		angular_v;//���ٶ�
		
}rcv_data;

typedef __packed struct
{
	uint8_t Header;
	uint8_t Enable;
	double Vy;            //����
	double Vx;            //���� 
	double Spin;
}PCcmd;


void CMDReceive(Car_Status* CMDToSTM,UART_HandleTypeDef*);

#endif