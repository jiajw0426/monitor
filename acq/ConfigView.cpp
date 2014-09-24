// onfigView.cpp : 实现文件
//

#include "stdafx.h"
#include "acq.h"
#include "configView.h"


// ConfigView

IMPLEMENT_DYNCREATE(ConfigView, CFormView)

ConfigView::ConfigView()
	: CFormView(ConfigView::IDD)
{

}

ConfigView::~ConfigView()
{
}

void ConfigView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ConfigView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &ConfigView::OnBnClickedButton1)
END_MESSAGE_MAP()


// ConfigView 诊断

#ifdef _DEBUG
void ConfigView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ConfigView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ConfigView 消息处理程序

void ConfigView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

BOOL ConfigView::Create(LPCTSTR a , LPCTSTR b , DWORD c,
						const RECT& d, CWnd* e , UINT f, CCreateContext* g){
					return		CFormView::Create(a,b,c,d,e,f,g);
}
