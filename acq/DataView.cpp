// DataView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "acq.h"
#include "DataView.h"


// CDataView

IMPLEMENT_DYNCREATE(CDataView, CFormView)

CDataView::CDataView()
	: CFormView(CDataView::IDD)
{

}

CDataView::~CDataView()
{
}

void CDataView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDataView, CFormView)
END_MESSAGE_MAP()


// CDataView ���

#ifdef _DEBUG
void CDataView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDataView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDataView ��Ϣ�������


BOOL CDataView::Create(LPCTSTR a , LPCTSTR b , DWORD c,
						const RECT& d, CWnd* e , UINT f, CCreateContext* g){
					return		CFormView::Create(a,b,c,d,e,f,g);
}


