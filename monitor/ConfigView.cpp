#include "StdAfx.h"
#include "ConfigView.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(ConfigView, CView)

BEGIN_MESSAGE_MAP(ConfigView, CView)
END_MESSAGE_MAP()

ConfigView::ConfigView(void)
{
}

ConfigView::~ConfigView(void)
{
}
BOOL ConfigView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

void ConfigView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    if (!pDoc)
		return;
	pDC-> DrawText(_T("hesadallo world11"),CRect(50,50,200,200),DT_SINGLELINE|DT_LEFT|DT_VCENTER);
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

int ConfigView::OnCreate(LPCREATESTRUCT lpCreateStruct){
	/*if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	 m_tree.Create(WS_VISIBLE|WS_CHILD|WS_BORDER|TVS_HASLINES|TVS_HASBUTTONS|TVS_EDITLABELS|TVS_LINESATROOT|TVS_CHECKBOXES,CRect(0,0,0,0),this,IDC_TREECTRL);
	 m_tree.ModifyStyle(TVS_CHECKBOXES,0); */
     return CView::OnCreate(lpCreateStruct);
}

void ConfigView::OnInitialUpdate() {  
	  CView::OnInitialUpdate();
}