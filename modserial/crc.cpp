#include<windows.h>
#include "crc.h"

WORD CRC16(BYTE* pchMsg, WORD wDataLen)
{
        BYTE chCRCHi = 0xFF; // ��CRC�ֽڳ�ʼ��
        BYTE chCRCLo = 0xFF; // ��CRC�ֽڳ�ʼ��
        WORD wIndex;            // CRCѭ���е�����

        while (wDataLen--)
        {
                // ����CRC
                wIndex = chCRCLo ^ *pchMsg++ ;
                chCRCLo = chCRCHi ^ chCRCHTalbe[wIndex]; 
                chCRCHi = chCRCLTalbe[wIndex] ;
        }

        return ((chCRCHi << 8) | chCRCLo) ;
}

void CRC(BYTE* pchMsg, WORD wDataLen,byte* cmd)
{
        BYTE chCRCHi = 0xFF; // ��CRC�ֽڳ�ʼ��
        BYTE chCRCLo = 0xFF; // ��CRC�ֽڳ�ʼ��
        WORD wIndex;            // CRCѭ���е�����

        while (wDataLen--)
        {
                // ����CRC
                wIndex = chCRCLo ^ *pchMsg++ ;
                chCRCLo = chCRCHi ^ chCRCHTalbe[wIndex]; 
                chCRCHi = chCRCLTalbe[wIndex] ;
        }
       cmd[6]=chCRCLo;
       cmd[7]=chCRCHi;
      // ((chCRCHi << 8) | chCRCLo) ;
}

