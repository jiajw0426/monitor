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
//���崮�ڽ������ݺ���������
typedef void (CALLBACK* ONSERIESREAD)(CWnd* pWnd,BYTE* buf,int bufLen);
class  __declspec( dllexport )  CCESeries  
{
public:
	CCESeries();
	virtual ~CCESeries();
	char ConvertHexChar(TCHAR ch);
	int String2Hex(CString str, CByteArray &senddata);
public:
	//�򿪴���
	BOOL OpenPort(//CWnd* pPortOwner,			/*ʹ�ô����࣬������*/
				  UINT portNo	= 1,		/*���ں�*/
				  UINT baud		= 9600,	/*������*/
				  UINT parity	= NOPARITY, /*��żУ��*/
				  UINT databits	= 8,		/*����λ*/
				  UINT stopbits	= 0        /*ֹͣλ*/
				  );
	//�رմ���
	void ClosePort();
	//���ô��ڶ�ȡ��д�볬ʱ
	BOOL SetSeriesTimeouts(COMMTIMEOUTS CommTimeOuts);
	void SetDTREnable(BOOL State);
	void SetRTSEnable(BOOL State);
	BOOL GetCTSState();
	UINT len;
	BOOL WritePort(HANDLE hComm,const BYTE *buf,DWORD bufLen);
//	BOOL WriteAByte(const BYTE& WriteData);
//	BOOL ReadAByte(BYTE& ReadData);
	//��д�߳�ID��ʶ
	DWORD m_dwReadThreadID;
		//���߳��˳��¼�
	HANDLE m_hReadCloseEvent;

//private:
    //�Ѵ򿪵Ĵ��ھ��
	HANDLE	m_hComm;
	CWnd* m_pPortOwner;
	//���߳̾��
	HANDLE m_hReadThread;
//	BOOL CWritePort(HANDLE hComm,const WCHAR* buf,DWORD bufLen);
//	BOOL ReadPort(HANDLE hComm,BYTE *buf,UINT bufLen);
	//ONSERIESREAD m_OnSeriesRead; //���ڶ�ȡ�ص�����

	void read(CWnd* pPortOwner,BYTE *buf,UINT bufLen);
	void OpenThread(CWnd* pPortOwner);

	ONSERIESREAD m_OnSeriesRead; //���ڶ�ȡ�ص�����
private:
	//�رն��߳�
	void CloseReadThread();
    //���ڶ��̺߳���
     static  DWORD WINAPI ReadThreadFunc(LPVOID lparam);

};

#endif // !defined(AFX_CESERIES_H__59599127_805E_4B0A_A132_B7C2237DEECB__INCLUDED_)
