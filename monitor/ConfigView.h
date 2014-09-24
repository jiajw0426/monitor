#pragma once
#include "afxwin.h"
#include "monitordoc.h"

class ConfigView :
	public CView
{
protected: // 仅从序列化创建
	
	DECLARE_DYNCREATE(ConfigView)
protected:
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
private:
	CTreeCtrl m_tree; 

public:
	virtual void OnDraw(CDC* pDC);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate(); // 重写以绘制该视图
	
public:
	ConfigView(void);
	~ConfigView(void);
protected:
	DECLARE_MESSAGE_MAP()
};
