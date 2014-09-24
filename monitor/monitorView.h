// monitorView.h : CmonitorView ��Ľӿ�
//


#pragma once
#include "monitordoc.h"


class CmonitorView : public CView
{
protected: // �������л�����
	
	DECLARE_DYNCREATE(CmonitorView)

// ����

// ����
public:
	CmonitorView();
    CmonitorDoc* GetDocument() const;
	afx_msg void OnButtonDown();
// ��д
public:
	virtual void OnInitialUpdate(); 
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:

	CButton m_Button;

// ʵ��
public:
	virtual ~CmonitorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // testegView.cpp �еĵ��԰汾
inline CmonitorDoc* CmonitorView::GetDocument() const
   { return reinterpret_cast<CmonitorDoc*>(m_pDocument); }
#endif
