// acqView.cpp : CacqView 类的实现
//

#include "stdafx.h"
#include "acq.h"

#include "acqDoc.h"
#include "acqView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CacqView

IMPLEMENT_DYNCREATE(CacqView, CFormView)

BEGIN_MESSAGE_MAP(CacqView, CFormView)
	ON_EN_CHANGE(IDC_EDIT2, &CacqView::OnEnChangeEdit2)
END_MESSAGE_MAP()

// CacqView 构造/析构

CacqView::CacqView()
	: CFormView(CacqView::IDD)
{
	// TODO: 在此处添加构造代码

}

CacqView::~CacqView()
{
}

void CacqView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CacqView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}



void CacqView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();


}


// CacqView 诊断

#ifdef _DEBUG
void CacqView::AssertValid() const
{
	CFormView::AssertValid();
}

CacqDoc* CacqView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CacqDoc)));
	return (CacqDoc*)m_pDocument;
}
#endif //_DEBUG


// CacqView 消息处理程序

void CacqView::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CFormView::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
