#pragma once
#include "afxwin.h"
#include "monitordoc.h"

class ConfigView :
	public CView
{
protected: // �������л�����
	
	DECLARE_DYNCREATE(ConfigView)
protected:
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CTreeCtrl m_tree; 

public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate(); // ��д�Ի��Ƹ���ͼ
	
public:
	ConfigView(void);
	~ConfigView(void);
protected:
	DECLARE_MESSAGE_MAP()
};
