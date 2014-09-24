// acqView.h : CacqView 类的接口
//
#pragma once

class CacqView : public CFormView
{
protected: // 仅从序列化创建
	CacqView();
	DECLARE_DYNCREATE(CacqView)

public:
	enum{ IDD = IDD_ACQ_FORM };

// 属性
public:
	CacqDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CacqView();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit2();
};

#ifndef _DEBUG  // acqView.cpp 中的调试版本
inline CacqDoc* CacqView::GetDocument() const
   { return reinterpret_cast<CacqDoc*>(m_pDocument); }
#endif

