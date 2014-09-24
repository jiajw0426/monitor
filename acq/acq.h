// acq.h : acq 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CacqApp:
// 有关此类的实现，请参阅 acq.cpp
//

class CacqApp : public CWinApp
{
public:
	CacqApp();

// 重写
public:
	virtual BOOL InitInstance();
	CView* SwitchView(CRuntimeClass* clazz);

// 实现
public:
	afx_msg void OnAppAbout();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnLogin();
	afx_msg void OnEditConfig();
};

extern CacqApp theApp;
