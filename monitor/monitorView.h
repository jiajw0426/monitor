// monitorView.h : CmonitorView 类的接口
//


#pragma once
#include "monitordoc.h"


class CmonitorView : public CView
{
protected: // 仅从序列化创建
	
	DECLARE_DYNCREATE(CmonitorView)

// 属性

// 操作
public:
	CmonitorView();
    CmonitorDoc* GetDocument() const;
	afx_msg void OnButtonDown();
// 重写
public:
	virtual void OnInitialUpdate(); 
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:

	CButton m_Button;

// 实现
public:
	virtual ~CmonitorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // testegView.cpp 中的调试版本
inline CmonitorDoc* CmonitorView::GetDocument() const
   { return reinterpret_cast<CmonitorDoc*>(m_pDocument); }
#endif
