// acqView.h : CacqView ��Ľӿ�
//
#pragma once

class CacqView : public CFormView
{
protected: // �������л�����
	CacqView();
	DECLARE_DYNCREATE(CacqView)

public:
	enum{ IDD = IDD_ACQ_FORM };

// ����
public:
	CacqDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CacqView();
#ifdef _DEBUG
	virtual void AssertValid() const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit2();
};

#ifndef _DEBUG  // acqView.cpp �еĵ��԰汾
inline CacqDoc* CacqView::GetDocument() const
   { return reinterpret_cast<CacqDoc*>(m_pDocument); }
#endif

