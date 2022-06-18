#include "CarStatus.h"


const int k=36;

Car_Status Creat_Car_Status(double vy,double vx,double spin)
{
	Car_Status status={.a=95.5,.b=100.25,.r=26,.Vy=vy,.Vx=vx,.Spin=spin};
	return status;
}


TCMD_HEX StatusToCMD_1_LF(Car_Status status)
{
	TCMD_HEX CMDToMotor1;

	int32_t v1=-(status.Vy+status.Vx-status.Spin*(status.a+status.b))/status.r*k;
	
	CMDToMotor1.Header=0xAA;
	CMDToMotor1.ID=1;
	CMDToMotor1.wr='w';
	CMDToMotor1.CMD=1;
	CMDToMotor1.Value=v1;
	CMDToMotor1.Loop=-1;
	CMDToMotor1.Num_Para=-1;
	CMDToMotor1.End=0x0D;
	CMDToMotor1.Check=0x0A;
	
	return CMDToMotor1;
}

TCMD_HEX StatusToCMD_2_LR(Car_Status status)
{
	TCMD_HEX CMDToMotor2;
	

	int32_t v2=-(status.Vy-status.Vx-status.Spin*(status.a+status.b))/status.r*k;
	
	CMDToMotor2.Header=0xAA;
	CMDToMotor2.ID=2;
	CMDToMotor2.wr='w';
	CMDToMotor2.CMD=1;
	CMDToMotor2.Value=v2;
	CMDToMotor2.Loop=-1;
	CMDToMotor2.Num_Para=-1;
	CMDToMotor2.End=0x0D;
	CMDToMotor2.Check=0x0A;
	
	return CMDToMotor2;
}

TCMD_HEX StatusToCMD_3_RF(Car_Status status)
{
	TCMD_HEX CMDToMotor3;

	int32_t v3=(status.Vy-status.Vx+status.Spin*(status.a+status.b))/status.r*k;
	
	CMDToMotor3.Header=0xAA;
	CMDToMotor3.ID=3;
	CMDToMotor3.wr='w';
	CMDToMotor3.CMD=1;
	CMDToMotor3.Value=v3;
	CMDToMotor3.Loop=-1;
	CMDToMotor3.Num_Para=-1;
	CMDToMotor3.End=0x0D;
	CMDToMotor3.Check=0x0A;
	
	return CMDToMotor3;
}

TCMD_HEX StatusToCMD_4_RR(Car_Status status)
{
	TCMD_HEX CMDToMotor4;
	
	int32_t v4=(status.Vy+status.Vx+status.Spin*(status.a+status.b))/status.r*k;
	
	CMDToMotor4.Header=0xAA;
	CMDToMotor4.ID=4;
	CMDToMotor4.wr='w';
	CMDToMotor4.CMD=1;
	CMDToMotor4.Value=v4;
	CMDToMotor4.Loop=-1;
	CMDToMotor4.Num_Para=-1;
	CMDToMotor4.End=0x0D;
	CMDToMotor4.Check=0x0A;
	
	return CMDToMotor4;
}

TCMD_HEX StatusToCMD(Car_Status status,int ID)
{
	switch(ID)
	{
		case 1:
			return StatusToCMD_1_LF(status);
		break;
		case 2:
			return StatusToCMD_2_LR(status);
		break;
		case 3:
			return StatusToCMD_3_RF(status);
		break;
		case 4:
			return StatusToCMD_4_RR(status);
		break;
		default:
			break;
	}
}

TCMD_HEX Enable_CMD(uint8_t id)
{
	TCMD_HEX CMDE;
	
	
	CMDE.Header=0xAA;
	CMDE.ID=id;
	CMDE.wr='w';
	CMDE.CMD=0;
	CMDE.Value=1;
	CMDE.Loop=-1;
	CMDE.Num_Para=-1;
	CMDE.End=0x0D;
	CMDE.Check=0x0A;
	
	return CMDE;
}

TCMD_HEX Forbid_CMD(uint8_t id)
{
	TCMD_HEX CMDF;
	
	
	CMDF.Header=0xAA;
	CMDF.ID=id;
	CMDF.wr='w';
	CMDF.CMD=0;
	CMDF.Value=1;
	CMDF.Loop=-1;
	CMDF.Num_Para=-1;
	CMDF.End=0x0D;
	CMDF.Check=0x0A;
	
	return CMDF;
}

TCMD_HEX Stop_CMD(uint8_t id)
{
	TCMD_HEX CMDF;
	
	
	CMDF.Header=0xAA;
	CMDF.ID=id;
	CMDF.wr='w';
	CMDF.CMD=3;
	CMDF.Value=0;
	CMDF.Loop=-1;
	CMDF.Num_Para=0;
	CMDF.End=0x0D;
	CMDF.Check=0x0A;
	
	return CMDF;
}

