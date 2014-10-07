#include<windows.h>
#include "crc.h"
#include "modbus.h"

void buidReadCmd(int addr,int stratReg,int count,BYTE* cmd){
	 cmd[0]=addr;
	 cmd[1]=0x03;
	 cmd[2]=stratReg>>8;
	 cmd[3]=stratReg&0x00ff;
	 cmd[4]=count>>8;
	 cmd[5]=count&0x00ff;
	 CRC(cmd,6,cmd);

}