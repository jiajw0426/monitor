// monitorView.cpp : CmonitorView ���ʵ��
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

// CmonitorView ����/����

CmonitorView::CmonitorView()
{
	// TODO: �ڴ˴���ӹ������

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
	m_Button.Create(_T("��½"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(l,t,r,b), this, LOGIN_BUTTONID);
  

}  
BOOL CmonitorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}


// CmonitorView ����
void CmonitorView::OnDraw(CDC* pDC)
{
	CmonitorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//pDC-> DrawText(_T("hesadallo world11"),CRect(50,100,200,200),DT_SINGLELINE|DT_LEFT|DT_VCENTER);

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CmonitorView::OnButtonDown()
{
	printf("abbb");
}

// CmonitorView ���

#ifdef _DEBUG
void CmonitorView::AssertValid() const
{
	CView::AssertValid();
}

CmonitorDoc* CmonitorView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmonitorDoc)));
	return (CmonitorDoc*)m_pDocument;
}
#endif //_DEBUG


// CmonitorView ��Ϣ�������
