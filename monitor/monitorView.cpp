// monitorView.cpp : CmonitorView 类的实现
//

#include "stdafx.h"
#include "monitor.h"
#include "MainFrm.h"
#include "monitorDoc.h"
#include "monitorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define LOGIN_BUTTONID 10000
#define LOGIN_BUTTONID_WIDTH 100
// CmonitorView

IMPLEMENT_DYNCREATE(CmonitorView, CView)

BEGIN_MESSAGE_MAP(CmonitorView, CView)
	ON_BN_CLICKED(LOGIN_BUTTONID,CmonitorView::OnButtonDown)
END_MESSAGE_MAP()

// CmonitorView 构造/析构

CmonitorView::CmonitorView()
{
	// TODO: 在此处添加构造代码

}

CmonitorView::~CmonitorView()
{
}
void CmonitorView::OnInitialUpdate(){
	 CView::OnInitialUpdate();
	CMainFrame *pMainWnd=(CMainFrame*)AfxGetMainWnd();
	CRect wndRect1;
	pMainWnd->GetClientRect(&wndRect1);
	int l=(wndRect1.right-LOGIN_BUTTONID_WIDTH)/2;
	int t=(wndRect1.bottom-28)/2-28;
	int r=l+LOGIN_BUTTONID_WIDTH;
	int b=t+28;
    pMainWnd->monitorView=this;
	m_Button.Create(_T("登陆"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(l,t,r,b), this, LOGIN_BUTTONID);
  

}  
BOOL CmonitorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}


// CmonitorView 绘制
void CmonitorView::OnDraw(CDC* pDC)
{
	CmonitorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//pDC-> DrawText(_T("hesadallo world11"),CRect(50,100,200,200),DT_SINGLELINE|DT_LEFT|DT_VCENTER);

	// TODO: 在此处为本机数据添加绘制代码
}

void CmonitorView::OnButtonDown()
{
	printf("abbb");
}

// CmonitorView 诊断

#ifdef _DEBUG
void CmonitorView::AssertValid() const
{
	CView::AssertValid();
}

CmonitorDoc* CmonitorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmonitorDoc)));
	return (CmonitorDoc*)m_pDocument;
}
#endif //_DEBUG


// CmonitorView 消息处理程序
