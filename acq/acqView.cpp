// acqView.cpp : CacqView ���ʵ��
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

// CacqView ����/����

CacqView::CacqView()
	: CFormView(CacqView::IDD)
{
	// TODO: �ڴ˴���ӹ������

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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}



void CacqView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();


}


// CacqView ���

#ifdef _DEBUG
void CacqView::AssertValid() const
{
	CFormView::AssertValid();
}

CacqDoc* CacqView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CacqDoc)));
	return (CacqDoc*)m_pDocument;
}
#endif //_DEBUG


// CacqView ��Ϣ�������

void CacqView::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CFormView::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
