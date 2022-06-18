

#include "PCtrans.h"
#include "string.h"


#define RECEIVELEN 100

//浮点数与HEX快速获取


uint32_t rx1_len;
uint8_t RX1_Buf[100];

rcv_data	com_x_rcv_data;//数据接收

int8_t get_data_analyze(uint8_t	*pdata)
{
	
	int8_t ret=0;
	int8_t	crc = 0;
	int8_t  p_crc = 0;
	if((*(pdata + 0) == 0xff) && (*(pdata + 1) == 0xff)){
		crc = (*(pdata + 2))^(*(pdata + 3))^(*(pdata + 4))^(*(pdata + 5))^(*(pdata + 6))^(*(pdata + 7))^(*(pdata + 8))^(*(pdata + 9))^(*(pdata + 10))^(*(pdata + 11))^(*(pdata + 12))^(*(pdata + 13));
		p_crc = (int8_t)(*(pdata + 14));//不进行类型转换，负数不正常
	}
	else{
		ret = -1;
		return ret;
	}
	if(p_crc != crc ){//校验和分析有误
		ret = -1;
		return ret;
	}
	//数据包分析正确，提取数据
	memset(&com_x_rcv_data,0,sizeof(com_x_rcv_data));
	com_x_rcv_data.linear_vx.cv[0] = *(pdata + 2);
	com_x_rcv_data.linear_vx.cv[1] = *(pdata + 3);
	com_x_rcv_data.linear_vx.cv[2] = *(pdata + 4);
	com_x_rcv_data.linear_vx.cv[3] = *(pdata + 5);
	
	com_x_rcv_data.linear_vy.cv[0] = *(pdata + 6);
	com_x_rcv_data.linear_vy.cv[1] = *(pdata + 7);
	com_x_rcv_data.linear_vy.cv[2] = *(pdata + 8);
	com_x_rcv_data.linear_vy.cv[3] = *(pdata + 9);
	
	com_x_rcv_data.angular_v.cv[0] = *(pdata + 10);
	com_x_rcv_data.angular_v.cv[1] = *(pdata + 11);
	com_x_rcv_data.angular_v.cv[2] = *(pdata + 12);
	com_x_rcv_data.angular_v.cv[3] = *(pdata + 13);
	
	return ret;
	
}

void CMDReceive(Car_Status* CMDToStatus,UART_HandleTypeDef* huart1)
{
	if(__HAL_UART_GET_FLAG(huart1,UART_FLAG_IDLE)!= RESET)
	{
		__HAL_UART_CLEAR_IDLEFLAG(huart1);
		HAL_UART_DMAStop(huart1);
		rx1_len= RECEIVELEN - __HAL_DMA_GET_COUNTER(huart1->hdmarx);
		HAL_UART_Receive_DMA(huart1,RX1_Buf,RECEIVELEN);
		
		if(get_data_analyze(RX1_Buf)!=-1)
		{
			CMDToStatus->Vx=com_x_rcv_data.linear_vx.fv;
			CMDToStatus->Vy=com_x_rcv_data.linear_vy.fv;
			CMDToStatus->Spin=com_x_rcv_data.angular_v.fv;
			
			/*
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
			HAL_Delay(500);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
			HAL_Delay(200);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
			HAL_Delay(300);
			HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
			*/
		}
		else
		{
			CMDToStatus->Vx=0;
			CMDToStatus->Vy=0;
			CMDToStatus->Spin=0;
		}
	}
}

