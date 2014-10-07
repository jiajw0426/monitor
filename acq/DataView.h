#pragma once
#include "ConfigDataControl.h"
#include "afxmt.h"
#include "afxwin.h"

// CDataView 窗体视图

class CDataView : public CFormView
{
	DECLARE_DYNCREATE(CDataView)

public:
	CDataView();  
	std::vector<CConfigDataControl*> controls;
	BOOL Create(LPCTSTR , LPCTSTR , DWORD,
		const RECT&, CWnd*, UINT, CCreateContext*);// 动态创建所使用的受保护的构造函数
	virtual ~CDataView();

public:
	enum { IDD = IDD_ACQ_DATA };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:

	void StartAcquisition();
    void StopAcquisition();
	void initControls();
	CCriticalSection g_criSection;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    void  OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void onStartAcquisition();
	afx_msg void onStopAcquisition();
	CButton startButton;
	CButton stopButton;
};


