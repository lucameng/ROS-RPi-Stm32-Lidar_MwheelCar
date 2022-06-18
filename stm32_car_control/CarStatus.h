#ifndef __SOMEFILE_C_

#define __SOMEFILE_C_

#include "stdint.h"

#define LEFT_FRONT 1
#define LEFT_REAR 2
#define RIGHT_FRONT 3
#define RIGHT_REAR 4

typedef __packed struct
{
	const double a,b,r;  // cm,aºáÏò,b×ÝÏò,r°ë¾¶
	double Vy;            //×ÝÏò
	double Vx;            //ºáÏò 
	double Spin;
}Car_Status;

Car_Status Creat_Car_Status(double vy,double vx,double spin);

typedef __packed struct//=36B
{ 
uint8_t Header; // Constant value 0xAA
uint8_t ID;// 0x00~0x63
uint8_t wr;// ‘w’ or ’r’; ‘w’ for sending command; ‘r’ for reading data
uint8_t CMD;// 0: Enable/Disable; 1: Normal loop operation; 2: Reset operation; 3: Braking operation. Other value: parameters’ setting
int32_t Value;// Control input value or parameter value
int32_t P; // Value of 10000*P, =0; -1 represents no change operation
int32_t I; // Value of 10000*I, =0; -1 represents no change operation
int32_t D; // Value of 10000*D, =0; -1 represents no change operation
int32_t S;// Value of 100*slope rate, >0; -1 represents no change operation
int32_t LMax; // LMax represents maximum value of controller’s output (speed, position, external sensor). The unit is mA
int32_t FeedFWCurrent; // Feed-forward current (mA). Typically, this value is 0 unless required for feed-forward applications.
int8_t Loop;// Index of closed-loop type. 0:Open loop; 1:Current loop; 2: Speed loop; 3: Position loop; 4: External sensor loop; -1:No change, depending on the last operation
int8_t Num_Para; // Index of PID setting. 0 represents normal operation; -1 represents no change operation
uint8_t End;// Constant char ’\r’ or 0x0D or decimal value 13
uint8_t Check;// Constant 0x0A or variable sum of all above bytes, depending on check type setting (CMD=241, Value=0 or 1)
}TCMD_HEX;

TCMD_HEX StatusToCMD(Car_Status status,int ID);


TCMD_HEX StatusToCMD_1_LF(Car_Status status);
TCMD_HEX StatusToCMD_2_LR(Car_Status status);
TCMD_HEX StatusToCMD_3_RF(Car_Status status);
TCMD_HEX StatusToCMD_4_RR(Car_Status status);

TCMD_HEX Enable_CMD(uint8_t id);
TCMD_HEX Forbid_CMD(uint8_t id);
TCMD_HEX Stop_CMD(uint8_t id);

#endif