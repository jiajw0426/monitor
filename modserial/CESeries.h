// CESeries.h: interface for the CCESeries class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CESERIES_H__59599127_805E_4B0A_A132_B7C2237DEECB__INCLUDED_)
#define AFX_CESERIES_H__59599127_805E_4B0A_A132_B7C2237DEECB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#include <windows.h>
#include <afxwin.h>
#endif // _MSC_VER > 1000
//定义串口接收数据函数的类型
typedef void (CALLBACK* ONSERIESREAD)(CWnd* pWnd,BYTE* buf,int bufLen);
class  __declspec( dllexport )  CCESeries  
{
public:
	CCESeries();
	virtual ~CCESeries();
	char ConvertHexChar(TCHAR ch);
	int String2Hex(CString str, CByteArray &senddata);
public:
	//打开串口
	BOOL OpenPort(//CWnd* pPortOwner,			/*使用串口类，窗体句柄*/
				  UINT portNo	= 1,		/*串口号*/
				  UINT baud		= 9600,	/*波特率*/
				  UINT parity	= NOPARITY, /*奇偶校验*/
				  UINT databits	= 8,		/*数据位*/
				  UINT stopbits	= 0        /*停止位*/
				  );
	//关闭串口
	void ClosePort();
	//设置串口读取、写入超时
	BOOL SetSeriesTimeouts(COMMTIMEOUTS CommTimeOuts);
	void SetDTREnable(BOOL State);
	void SetRTSEnable(BOOL State);
	BOOL GetCTSState();
	UINT len;
	BOOL WritePort(HANDLE hComm,const BYTE *buf,DWORD bufLen);
//	BOOL WriteAByte(const BYTE& WriteData);
//	BOOL ReadAByte(BYTE& ReadData);
	//读写线程ID标识
	DWORD m_dwReadThreadID;
		//读线程退出事件
	HANDLE m_hReadCloseEvent;

//private:
    //已打开的串口句柄
	HANDLE	m_hComm;
	CWnd* m_pPortOwner;
	//读线程句柄
	HANDLE m_hReadThread;
//	BOOL CWritePort(HANDLE hComm,const WCHAR* buf,DWORD bufLen);
//	BOOL ReadPort(HANDLE hComm,BYTE *buf,UINT bufLen);
	//ONSERIESREAD m_OnSeriesRead; //串口读取回调函数

	void read(CWnd* pPortOwner,BYTE *buf,UINT bufLen);
	void OpenThread(CWnd* pPortOwner);

	ONSERIESREAD m_OnSeriesRead; //串口读取回调函数
private:
	//关闭读线程
	void CloseReadThread();
    //串口读线程函数
     static  DWORD WINAPI ReadThreadFunc(LPVOID lparam);

};

#endif // !defined(AFX_CESERIES_H__59599127_805E_4B0A_A132_B7C2237DEECB__INCLUDED_)
