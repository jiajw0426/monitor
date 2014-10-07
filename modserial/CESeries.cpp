// CESeries.cpp: implementation of the CCESeries class.
//
//////////////////////////////////////////////////////////////////////


#include<windows.h>
#include "CESeries.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//��CCESeries���캯��
CCESeries::CCESeries()
{
	m_hComm = INVALID_HANDLE_VALUE;
	len=0;
}

//��CCESeries��������
CCESeries::~CCESeries()
{
	
}

/*
*�������ܣ��򿪴���
*��ڲ�����
		   portNo		:���ں�
		   baud			:������
		   parity		:��żУ��
		   databits		:����λ
		   stopbits		:ֹͣλ
*���ڲ�����(��)
*����ֵ��TRUE:�ɹ��򿪴���;FALSE:�򿪴���ʧ��
*/
BOOL CCESeries::OpenPort(//CWnd* pPortOwner,
						 UINT portNo	,			/*���ں�*/
						 UINT baud		,			/*������*/
						 UINT parity	,			/*��żУ��*/
						 UINT databits	,			/*����λ*/
						 UINT stopbits			   /*ֹͣλ*/
						 )
{
	
	DCB commParam;
	TCHAR szPort[15];	
	
	// �Ѿ��򿪵Ļ���ֱ�ӷ���
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		return TRUE;
	}
//	ASSERT(pPortOwner != NULL);
//	ASSERT(portNo > 0 && portNo < 5);
	
	//���ô�����
	wsprintf(szPort, L"COM%d:", portNo);
	//�򿪴���
	m_hComm = CreateFile(
		szPort,
		GENERIC_READ | GENERIC_WRITE,	//�������д
		0,								//��ռ��ʽ������ģʽ��
		NULL,
		OPEN_EXISTING,					//�򿪶����Ǵ�����������ʽ��
		0,
		NULL 
		);
	
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		// ��Ч���,���ء�		
		TRACE(_T("CreateFile ������Ч���"));
		return FALSE;
		
	}
	
	// �õ��򿪴��ڵĵ�ǰ���Բ������޸ĺ����������ô��ڡ�
	// ���ô��ڵĳ�ʱ����Ϊ�������ء�
	
	if (!GetCommState(m_hComm,&commParam))
	{		
		return FALSE;
	}
	
	commParam.BaudRate = baud;					// ���ò����� 
	commParam.fBinary = TRUE;					// ���ö�����ģʽ���˴���������TRUE
	commParam.fParity = TRUE;					// ֧����żУ�� 
	commParam.ByteSize = databits;				// ����λ,��Χ:4-8 
	commParam.Parity = NOPARITY;				// У��ģʽ
	commParam.StopBits = stopbits;				// ֹͣλ 
	
	commParam.fOutxCtsFlow = FALSE;				// No CTS output flow control 
	commParam.fOutxDsrFlow = FALSE;				// No DSR output flow control 
	commParam.fDtrControl = DTR_CONTROL_ENABLE; 
	// DTR flow control type 
	commParam.fDsrSensitivity = FALSE;			// DSR sensitivity 
	commParam.fTXContinueOnXoff = TRUE;			// XOFF continues Tx 
	commParam.fOutX = FALSE;					// No XON/XOFF out flow control 
	commParam.fInX = FALSE;						// No XON/XOFF in flow control 
	commParam.fErrorChar = FALSE;				// Disable error replacement 
	commParam.fNull = FALSE;					// Disable null stripping 
	commParam.fRtsControl = RTS_CONTROL_ENABLE; 
	// RTS flow control 
	commParam.fAbortOnError = FALSE;			// �����ڷ������󣬲�����ֹ���ڶ�д
	
	if (!SetCommState(m_hComm, &commParam))
	{
		TRACE(_T("SetCommState error"));		
		return FALSE;
	}
	
	
    //���ô��ڶ�дʱ��
	COMMTIMEOUTS CommTimeOuts;
	GetCommTimeouts (m_hComm, &CommTimeOuts);
	CommTimeOuts.ReadIntervalTimeout = MAXDWORD;  
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;  
	CommTimeOuts.ReadTotalTimeoutConstant = 0;    
	CommTimeOuts.WriteTotalTimeoutMultiplier = 10;  
	CommTimeOuts.WriteTotalTimeoutConstant = 1000;  
	
	if(!SetCommTimeouts( m_hComm, &CommTimeOuts ))
	{
		TRACE( _T("SetCommTimeouts ���ش���") );
		return FALSE;
	}
	
//	m_pPortOwner = pPortOwner;	
	
	//ָ���˿ڼ����¼���
	SetCommMask (m_hComm, EV_RXCHAR);
	
	//�����豸������
	SetupComm(m_hComm,512,512);
	
	//��ʼ���������е���Ϣ
	PurgeComm(m_hComm,PURGE_TXCLEAR|PURGE_RXCLEAR);
	
//	m_hReadCloseEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
//	m_hWriteCloseEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	//�����������߳�
//	m_hReadThread = CreateThread(NULL,0,ReadThreadFunc,this,0,&m_dwReadThreadID);
	//����д�����߳�
//	m_hWriteThread = CreateThread(NULL,0,WriteThreadFunc,this,0,&m_dwWriteThreadID);
	
	TRACE(_T("���ڴ򿪳ɹ�"));
	
	return TRUE;
}

/*
*�������ܣ��رմ���
*��ڲ�����(��)
*���ڲ�����(��)
*����ֵ��  (��)
*/
void CCESeries::ClosePort()
{	
	//��ʾ���ڻ�û�д�
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		return ;
	}
	//�رն��߳�
	CloseReadThread();
	//�رմ���
	if (!CloseHandle (m_hComm))
	{
		m_hComm = INVALID_HANDLE_VALUE;
		return ;
	}
	m_hComm = INVALID_HANDLE_VALUE;
//	AfxMessageBox(_T("ClosePort"));
}
//�رն��߳�
void CCESeries::CloseReadThread()
{
	SetEvent(m_hReadCloseEvent);
	//���������¼���Ч��Ч
	SetCommMask(m_hComm, 0);
	//������н�Ҫ��������
    PurgeComm( m_hComm,  PURGE_RXCLEAR );
    //�ȴ�10�룬������߳�û���˳�����ǿ���˳�
    if (WaitForSingleObject(m_hReadThread,10000) == WAIT_TIMEOUT)
	{	
		TerminateThread(m_hReadThread,0);
	}
	m_hReadThread = NULL;
}
/*
*�������ܣ����ô��ڶ�ȡ��д�볬ʱ
*��ڲ�����CommTimeOuts : ָ��COMMTIMEOUTS�ṹ
*���ڲ�����(��)
*����ֵ��TRUE:���óɹ�;FALSE:����ʧ��
*/
BOOL CCESeries::SetSeriesTimeouts(COMMTIMEOUTS CommTimeOuts)
{
	ASSERT(m_hComm != INVALID_HANDLE_VALUE);
	return SetCommTimeouts(m_hComm,&CommTimeOuts);
}


//���ڶ��̺߳���
DWORD CCESeries::ReadThreadFunc(LPVOID lparam)
{
	CCESeries *ceSeries = (CCESeries*)lparam;
	
	DWORD	evtMask;
	BYTE * readBuf = NULL;//��ȡ���ֽ�
	DWORD actualReadLen=0;//ʵ�ʶ�ȡ���ֽ���
	DWORD willReadLen;
	BOOL fSuccess;
	
	DWORD dwReadErrors;
	COMSTAT	cmState;
	
	// ��ջ��壬����鴮���Ƿ�򿪡�
	ASSERT(ceSeries->m_hComm !=INVALID_HANDLE_VALUE); 
	
	
	//��մ���
	PurgeComm(ceSeries->m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR );
	
	fSuccess=SetCommMask (ceSeries->m_hComm, EV_RXCHAR | EV_CTS | EV_DSR );
	 if (!fSuccess) 
    {
        // Handle the error. 
        printf("SetCommMask failed with error %d.\n", GetLastError());
        return 1;
    }
	while (TRUE)
	{   	
		
		BOOL hasEvent=FALSE;
		try{
		hasEvent=WaitCommEvent(ceSeries->m_hComm,&evtMask,0);
		}catch(int){
		   printf("WaitCommEvent failed with error %d.\n", GetLastError());
		}
			
		if (hasEvent)
		{			
			SetCommMask (ceSeries->m_hComm, EV_RXCHAR | EV_CTS | EV_DSR );
			//��ʾ�����յ��ַ�		
			if (evtMask & EV_RXCHAR) 
			{
				
				ClearCommError(ceSeries->m_hComm,&dwReadErrors,&cmState);
				willReadLen = cmState.cbInQue ;
				if (willReadLen <= 0)
				{
					continue;
				}
				
				readBuf = new BYTE[willReadLen];
				ReadFile(ceSeries->m_hComm, readBuf, willReadLen, &actualReadLen,0);
				
				//�����ȡ�����ݴ���0��
				if (actualReadLen>0)
				{
				//	ceSeries->read(ceSeries->m_pPortOwner,readBuf,actualReadLen);
				//	AfxMessageBox(_T("ol"));
					//������ȡ�ص�����
					ceSeries->m_OnSeriesRead(ceSeries->m_pPortOwner,readBuf,actualReadLen);
				//	AfxMessageBox(_T("ol"));
				}
			}
		} 
		//����յ����߳��˳��źţ����˳��߳�
		if (WaitForSingleObject(ceSeries->m_hReadCloseEvent,500) == WAIT_OBJECT_0)
		{	AfxMessageBox(_T("exit"));
			break;
		}
	}
	return 0;
}

//˽�÷����������򴮿�д���ݣ���д�̵߳���
BOOL CCESeries::WritePort(HANDLE hComm,const BYTE *buf,DWORD bufLen)
{
//	AfxMessageBox( _T("WritePort") );
	DWORD dwNumBytesWritten;
	DWORD dwHaveNumWritten =0 ; //�Ѿ�д�����
	
	ASSERT(hComm != INVALID_HANDLE_VALUE);
	do
	{
	//	AfxMessageBox( _T("gogo") );
		if (WriteFile (hComm,					//���ھ�� 
			buf+dwHaveNumWritten,				//��д���ݻ����� 
			bufLen- dwHaveNumWritten,          //��д���ݻ�������С
			&dwNumBytesWritten,					//����ִ�гɹ��󣬷���ʵ���򴮿�д�ĸ���	
			NULL))								//�˴���������NULL
		{
			dwHaveNumWritten = dwHaveNumWritten + dwNumBytesWritten;
			//д�����
			if (dwHaveNumWritten == bufLen)
			{
			//	AfxMessageBox( _T("yes ok") );
				return TRUE;
			}
		//	Sleep(10);
		}
		else
		{
			return FALSE;
		}
	}while (TRUE);
	
	return TRUE;	
}
/*
BOOL CCESeries::WriteAByte(const BYTE& WriteData)
{
//	AfxMessageBox(L"WriteAByte");
	//INT  rc; 
	BOOL rc;
	DWORD  cBytes=0;
//	ASSERT(m_hComm != INVALID_HANDLE_VALUE);
//AfxMessageBox(_T("���ڴ�"));
	rc = WriteFile(m_hComm,&WriteData,1,&cBytes,NULL);

	if(!rc)
	{
     //����д����
        MessageBox(NULL,TEXT("con faikle!"),TEXT("faile"),MB_OK);
		ClosePort();
        return false;
	}

	if(cBytes == 1)
	{
	//	AfxMessageBox(L"yes");
		return true;
	}
	else
	{
		MessageBox(NULL,_T("�򴮿�д��һ���ֽ�ʧ��"),_T("error"),MB_ICONEXCLAMATION);
		ClosePort();
		return false;
	}
}

BOOL CCESeries::ReadAByte(BYTE& ReadData)
{
	//INT  rc;  
	BOOL rc;
	DWORD  cBytes;

//	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR );
	rc = ReadFile(m_hComm,&ReadData,1,&cBytes,NULL);
	
	if(!rc)
	{
     //����д����
        MessageBox(NULL,TEXT("���ܶ���������!"),TEXT("����"),MB_OK);
          // dwBytesWritten=0;
	}

	if(cBytes == 1)
	{
		return true;
	}
	else
	{
	//	MessageBox(NULL,_T("an error occured while reading a byte to port"),_T("error"),MB_ICONEXCLAMATION);
		return false;
	}
}
*/
void CCESeries::SetDTREnable(BOOL State)
{
	if(State)
		EscapeCommFunction(m_hComm,SETDTR);
	else
		EscapeCommFunction(m_hComm,CLRDTR);
}

void CCESeries::SetRTSEnable(BOOL State)
{
	if(State)
		EscapeCommFunction(m_hComm,SETRTS);
	else
		EscapeCommFunction(m_hComm,CLRRTS);
}

BOOL CCESeries::GetCTSState()
{
	DWORD State;
	State = MS_CTS_ON;
	GetCommModemStatus(m_hComm,&State);
	if(State&MS_CTS_ON)
		return TRUE;
	else
		return FALSE;
}
/*
BOOL CCESeries::ReadPort(HANDLE hComm,BYTE *buf,UINT bufLen)
{
	DWORD leng=0;
	DWORD willReadLen;
	DWORD dwReadErrors;
	COMSTAT cmState;
	ASSERT(m_hComm != INVALID_HANDLE_VALUE);
	//BYTE *readbuf=NULL;
	//readbuf= new BYTE[bufLen];	
	for(int i=1;i>0;i++)
	{
	ClearCommError(m_hComm,&dwReadErrors,&cmState);
	willReadLen = cmState.cbInQue;
			if(willReadLen<=0)
				{
					Sleep(1);
					continue;
				}
	BOOL rc;
	DWORD  cBytes=0;
	buf= new BYTE[willReadLen];
	rc = ReadFile(m_hComm,buf,willReadLen,&cBytes,NULL);
		if(!rc)
		{
			continue;
		}

		if(cBytes >0)
		{
			return TRUE;	
		}
	}
	return TRUE;	
}

BOOL CCESeries::CWritePort(HANDLE hComm, const WCHAR* buf, DWORD bufLen)
{
	DWORD dwNumBytesWritten=0;
	DWORD dwHaveNumWritten =0 ; //�Ѿ�д�����
	ASSERT(hComm != INVALID_HANDLE_VALUE);
	do
	{
	//	AfxMessageBox( _T("gogo") );
		if (WriteFile (hComm,					//���ھ�� 
			buf+dwHaveNumWritten,				//��д���ݻ����� 
			bufLen- dwHaveNumWritten,          //��д���ݻ�������С
			&dwNumBytesWritten,					//����ִ�гɹ��󣬷���ʵ���򴮿�д�ĸ���	
			NULL))								//�˴���������NULL
		{
			dwHaveNumWritten = dwHaveNumWritten + dwNumBytesWritten;
			//д�����
			if (dwHaveNumWritten == bufLen)
			{
				//AfxMessageBox( _T("yes ok") );
				return TRUE;
			}
			Sleep(10);
		}
		else
		{
			return FALSE;
		}
	}while (TRUE);
	
	return TRUE;	
}
*/
void CCESeries::OpenThread(CWnd* pPortOwner)
{
	m_pPortOwner = pPortOwner;	
	m_hReadCloseEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	//�����������߳�
	m_hReadThread = CreateThread(NULL,0,ReadThreadFunc,this,0,&m_dwReadThreadID);
}

void CCESeries::read(CWnd* pPortOwner,BYTE *buf,UINT bufLen)
{
	CString str,str1,str2;
	BYTE *pData;
	
	str2.Format(_T("%d"),len);
	str.Format(_T("%s"),buf);
//	pPortOwner->GetDlgItem(IDC_EDIT1)->GetWindowText(str1);
	str1+=str;
	{
		CByteArray hexdata;
		int Len=String2Hex(str1,hexdata); 
		///bufLen=len;
		pData=new BYTE[bufLen];
		for(int k=0;k<Len;k++)
		{
			pData[k]=hexdata[k];			
		}
		str1.Format(_T("%c"),pData);
	//	len+=Len;
	}
	len+=bufLen;
	//AfxMessageBox(str);
	//pPortOwner->OnSeriesRead(pPortOwner,buf,bufLen);
	//pPortOwner->GetDlgItem(IDC_EDIT1)->SetWindowText(str1);	
	//pPortOwner->GetDlgItem(IDC_EDIT4)->SetWindowText(str2);	
	return;
}
int CCESeries::String2Hex(CString str, CByteArray &senddata)
{
	int hexdata,lowhexdata;
	int hexdatalen=0;
	int len=str.GetLength();
	senddata.SetSize(len/2);
	for(int i=0;i<len;)
	{
	TCHAR lstr,hstr=str.GetAt(i);
	if(hstr==' ')
	{
	i++;
	continue;
	}
	i++;
	if(i>=len)
	break;
	lstr=str[i];
//	AfxMessageBox(str[i]);
	hexdata=ConvertHexChar(hstr);
	lowhexdata=ConvertHexChar(lstr);
	if((hexdata==16)||(lowhexdata==16))
	break;
	else 
	hexdata=hexdata*16+lowhexdata;
	i++;
	senddata[hexdatalen]=(char)hexdata;
	hexdatalen++;
	}
	senddata.SetSize(hexdatalen); 
	return hexdatalen;
	
}

char CCESeries::ConvertHexChar(TCHAR ch)
{
	if((ch>='0')&&(ch<='9'))
		return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
	else return(-1);
}
