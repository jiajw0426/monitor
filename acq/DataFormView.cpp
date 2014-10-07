// DataFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "acq.h"
#include "DataFormView.h"


// CDataFormView

IMPLEMENT_DYNCREATE(CDataFormView, CFormView)

CDataFormView::CDataFormView()
	: CFormView(CDataFormView::IDD)
{

}

CDataFormView::~CDataFormView()
{
}

void CDataFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDataFormView, CFormView)
END_MESSAGE_MAP()


// CDataFormView 诊断

#ifdef _DEBUG
void CDataFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDataFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDataFormView 消息处理程序
