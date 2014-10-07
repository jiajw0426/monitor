#include<windows.h>
#include "crc.h"

WORD CRC16(BYTE* pchMsg, WORD wDataLen)
{
        BYTE chCRCHi = 0xFF; // 高CRC字节初始化
        BYTE chCRCLo = 0xFF; // 低CRC字节初始化
        WORD wIndex;            // CRC循环中的索引

        while (wDataLen--)
        {
                // 计算CRC
                wIndex = chCRCLo ^ *pchMsg++ ;
                chCRCLo = chCRCHi ^ chCRCHTalbe[wIndex]; 
                chCRCHi = chCRCLTalbe[wIndex] ;
        }

        return ((chCRCHi << 8) | chCRCLo) ;
}

void CRC(BYTE* pchMsg, WORD wDataLen,byte* cmd)
{
        BYTE chCRCHi = 0xFF; // 高CRC字节初始化
        BYTE chCRCLo = 0xFF; // 低CRC字节初始化
        WORD wIndex;            // CRC循环中的索引

        while (wDataLen--)
        {
                // 计算CRC
                wIndex = chCRCLo ^ *pchMsg++ ;
                chCRCLo = chCRCHi ^ chCRCHTalbe[wIndex]; 
                chCRCHi = chCRCLTalbe[wIndex] ;
        }
       cmd[6]=chCRCLo;
       cmd[7]=chCRCHi;
      // ((chCRCHi << 8) | chCRCLo) ;
}

