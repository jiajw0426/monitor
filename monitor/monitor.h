// monitor.h : monitor Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#ifdef STANDARDSHELL_UI_MODEL
#include "resource.h"
#endif

// CmonitorApp:
// �йش����ʵ�֣������ monitor.cpp
//

class CmonitorApp : public CWinApp
{
public:
	CmonitorApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
public:
	afx_msg void OnAppAbout();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnLogin();
};

extern CmonitorApp theApp;
