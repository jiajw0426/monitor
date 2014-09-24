// MainFrm.h : CMainFrame ��Ľӿ�
//


#pragma once

#include  "monitorView.h"
#include  "ConfigView.h"
#define	  LOGIN_VIEW 2

class CMainFrame : public CFrameWnd
{
protected: // �������л�����
	CMainFrame();

	DECLARE_DYNCREATE(CMainFrame)

protected: 
	int showLoginView();
public:
    CmonitorView* monitorView;
	ConfigView*   configView;
// ����
public:

    int showView(int viewId);
	
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:  // �ؼ���Ƕ���Ա

	CCommandBar m_wndCommandBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
	DECLARE_MESSAGE_MAP()
};


