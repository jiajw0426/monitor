// MainFrm.h : CMainFrame 类的接口
//


#pragma once

#include  "monitorView.h"
#include  "ConfigView.h"
#define	  LOGIN_VIEW 2

class CMainFrame : public CFrameWnd
{
protected: // 仅从序列化创建
	CMainFrame();

	DECLARE_DYNCREATE(CMainFrame)

protected: 
	int showLoginView();
public:
    CmonitorView* monitorView;
	ConfigView*   configView;
// 操作
public:

    int showView(int viewId);
	
// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:  // 控件条嵌入成员

	CCommandBar m_wndCommandBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	DECLARE_MESSAGE_MAP()
};


