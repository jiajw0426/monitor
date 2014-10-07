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

//类CCESeries构造函数
CCESeries::CCESeries()
{
	m_hComm = INVALID_HANDLE_VALUE;
	len=0;
}

//类CCESeries析构函数
CCESeries::~CCESeries()
{
	
}

/*
*函数介绍：打开串口
*入口参数：
		   portNo		:串口号
		   baud			:波特率
		   parity		:奇偶校验
		   databits		:数据位
		   stopbits		:停止位
*出口参数：(无)
*返回值：TRUE:成功打开串口;FALSE:打开串口失败
*/
BOOL CCESeries::OpenPort(//CWnd* pPortOwner,
						 UINT portNo	,			/*串口号*/
						 UINT baud		,			/*波特率*/
						 UINT parity	,			/*奇偶校验*/
						 UINT databits	,			/*数据位*/
						 UINT stopbits			   /*停止位*/
						 )
{
	
	DCB commParam;
	TCHAR szPort[15];	
	
	// 已经打开的话，直接返回
	if (m_hComm != INVALID_HANDLE_VALUE)
	{
		return TRUE;
	}
//	ASSERT(pPortOwner != NULL);
//	ASSERT(portNo > 0 && portNo < 5);
	
	//设置串口名
	wsprintf(szPort, L"COM%d:", portNo);
	//打开串口
	m_hComm = CreateFile(
		szPort,
		GENERIC_READ | GENERIC_WRITE,	//允许读和写
		0,								//独占方式（共享模式）
		NULL,
		OPEN_EXISTING,					//打开而不是创建（创建方式）
		0,
		NULL 
		);
	
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		// 无效句柄,返回。		
		TRACE(_T("CreateFile 返回无效句柄"));
		return FALSE;
		
	}
	
	// 得到打开串口的当前属性参数，修改后再重新设置串口。
	// 设置串口的超时特性为立即返回。
	
	if (!GetCommState(m_hComm,&commParam))
	{		
		return FALSE;
	}
	
	commParam.BaudRate = baud;					// 设置波特率 
	commParam.fBinary = TRUE;					// 设置二进制模式，此处必须设置TRUE
	commParam.fParity = TRUE;					// 支持奇偶校验 
	commParam.ByteSize = databits;				// 数据位,范围:4-8 
	commParam.Parity = NOPARITY;				// 校验模式
	commParam.StopBits = stopbits;				// 停止位 
	
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
	commParam.fAbortOnError = FALSE;			// 当串口发生错误，并不终止串口读写
	
	if (!SetCommState(m_hComm, &commParam))
	{
		TRACE(_T("SetCommState error"));		
		return FALSE;
	}
	
	
    //设置串口读写时间
	COMMTIMEOUTS CommTimeOuts;
	GetCommTimeouts (m_hComm, &CommTimeOuts);
	CommTimeOuts.ReadIntervalTimeout = MAXDWORD;  
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;  
	CommTimeOuts.ReadTotalTimeoutConstant = 0;    
	CommTimeOuts.WriteTotalTimeoutMultiplier = 10;  
	CommTimeOuts.WriteTotalTimeoutConstant = 1000;  
	
	if(!SetCommTimeouts( m_hComm, &CommTimeOuts ))
	{
		TRACE( _T("SetCommTimeouts 返回错误") );
		return FALSE;
	}
	
//	m_pPortOwner = pPortOwner;	
	
	//指定端口监测的事件集
	SetCommMask (m_hComm, EV_RXCHAR);
	
	//分配设备缓冲区
	SetupComm(m_hComm,512,512);
	
	//初始化缓冲区中的信息
	PurgeComm(m_hComm,PURGE_TXCLEAR|PURGE_RXCLEAR);
	
//	m_hReadCloseEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
//	m_hWriteCloseEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	//创建读串口线程
//	m_hReadThread = CreateThread(NULL,0,ReadThreadFunc,this,0,&m_dwReadThreadID);
	//创建写串口线程
//	m_hWriteThread = CreateThread(NULL,0,WriteThreadFunc,this,0,&m_dwWriteThreadID);
	
	TRACE(_T("串口打开成功"));
	
	return TRUE;
}

/*
*函数介绍：关闭串口
*入口参数：(无)
*出口参数：(无)
*返回值：  (无)
*/
void CCESeries::ClosePort()
{	
	//表示串口还没有打开
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		return ;
	}
	//关闭读线程
	CloseReadThread();
	//关闭串口
	if (!CloseHandle (m_hComm))
	{
		m_hComm = INVALID_HANDLE_VALUE;
		return ;
	}
	m_hComm = INVALID_HANDLE_VALUE;
//	AfxMessageBox(_T("ClosePort"));
}
//关闭读线程
void CCESeries::CloseReadThread()
{
	SetEvent(m_hReadCloseEvent);
	//设置所有事件无效无效
	SetCommMask(m_hComm, 0);
	//清空所有将要读的数据
    PurgeComm( m_hComm,  PURGE_RXCLEAR );
    //等待10秒，如果读线程没有退出，则强制退出
    if (WaitForSingleObject(m_hReadThread,10000) == WAIT_TIMEOUT)
	{	
		TerminateThread(m_hReadThread,0);
	}
	m_hReadThread = NULL;
}
/*
*函数介绍：设置串口读取、写入超时
*入口参数：CommTimeOuts : 指向COMMTIMEOUTS结构
*出口参数：(无)
*返回值：TRUE:设置成功;FALSE:设置失败
*/
BOOL CCESeries::SetSeriesTimeouts(COMMTIMEOUTS CommTimeOuts)
{
	ASSERT(m_hComm != INVALID_HANDLE_VALUE);
	return SetCommTimeouts(m_hComm,&CommTimeOuts);
}


//串口读线程函数
DWORD CCESeries::ReadThreadFunc(LPVOID lparam)
{
	CCESeries *ceSeries = (CCESeries*)lparam;
	
	DWORD	evtMask;
	BYTE * readBuf = NULL;//读取的字节
	DWORD actualReadLen=0;//实际读取的字节数
	DWORD willReadLen;
	BOOL fSuccess;
	
	DWORD dwReadErrors;
	COMSTAT	cmState;
	
	// 清空缓冲，并检查串口是否打开。
	ASSERT(ceSeries->m_hComm !=INVALID_HANDLE_VALUE); 
	
	
	//清空串口
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
			//表示串口收到字符		
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
				
				//如果读取的数据大于0，
				if (actualReadLen>0)
				{
				//	ceSeries->read(ceSeries->m_pPortOwner,readBuf,actualReadLen);
				//	AfxMessageBox(_T("ol"));
					//触发读取回调函数
					ceSeries->m_OnSeriesRead(ceSeries->m_pPortOwner,readBuf,actualReadLen);
				//	AfxMessageBox(_T("ol"));
				}
			}
		} 
		//如果收到读线程退出信号，则退出线程
		if (WaitForSingleObject(ceSeries->m_hReadCloseEvent,500) == WAIT_OBJECT_0)
		{	AfxMessageBox(_T("exit"));
			break;
		}
	}
	return 0;
}

//私用方法，用于向串口写数据，被写线程调用
BOOL CCESeries::WritePort(HANDLE hComm,const BYTE *buf,DWORD bufLen)
{
//	AfxMessageBox( _T("WritePort") );
	DWORD dwNumBytesWritten;
	DWORD dwHaveNumWritten =0 ; //已经写入多少
	
	ASSERT(hComm != INVALID_HANDLE_VALUE);
	do
	{
	//	AfxMessageBox( _T("gogo") );
		if (WriteFile (hComm,					//串口句柄 
			buf+dwHaveNumWritten,				//被写数据缓冲区 
			bufLen- dwHaveNumWritten,          //被写数据缓冲区大小
			&dwNumBytesWritten,					//函数执行成功后，返回实际向串口写的个数	
			NULL))								//此处必须设置NULL
		{
			dwHaveNumWritten = dwHaveNumWritten + dwNumBytesWritten;
			//写入完成
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
//AfxMessageBox(_T("串口打开"));
	rc = WriteFile(m_hComm,&WriteData,1,&cBytes,NULL);

	if(!rc)
	{
     //不能写数据
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
		MessageBox(NULL,_T("向串口写入一个字节失败"),_T("error"),MB_ICONEXCLAMATION);
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
     //不能写数据
        MessageBox(NULL,TEXT("不能读串口数据!"),TEXT("错误！"),MB_OK);
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
	DWORD dwHaveNumWritten =0 ; //已经写入多少
	ASSERT(hComm != INVALID_HANDLE_VALUE);
	do
	{
	//	AfxMessageBox( _T("gogo") );
		if (WriteFile (hComm,					//串口句柄 
			buf+dwHaveNumWritten,				//被写数据缓冲区 
			bufLen- dwHaveNumWritten,          //被写数据缓冲区大小
			&dwNumBytesWritten,					//函数执行成功后，返回实际向串口写的个数	
			NULL))								//此处必须设置NULL
		{
			dwHaveNumWritten = dwHaveNumWritten + dwNumBytesWritten;
			//写入完成
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
	//创建读串口线程
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
