// acq.h : acq Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CacqApp:
// �йش����ʵ�֣������ acq.cpp
//

class CacqApp : public CWinApp
{
public:
	CacqApp();

// ��д
public:
	virtual BOOL InitInstance();
	CView* SwitchView(CRuntimeClass* clazz);

// ʵ��
public:
	afx_msg void OnAppAbout();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnLogin();
	afx_msg void OnEditConfig();
};

extern CacqApp theApp;
