// monitorDoc.cpp : CmonitorDoc ���ʵ��
//

#include "stdafx.h"
#include "monitor.h"

#include "monitorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmonitorDoc

IMPLEMENT_DYNCREATE(CmonitorDoc, CDocument)

BEGIN_MESSAGE_MAP(CmonitorDoc, CDocument)
END_MESSAGE_MAP()

// CmonitorDoc ����/����

CmonitorDoc::CmonitorDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CmonitorDoc::~CmonitorDoc()
{
}

BOOL CmonitorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}

// CmonitorDoc ���л�

#ifndef _WIN32_WCE_NO_ARCHIVE_SUPPORT
void CmonitorDoc::Serialize(CArchive& ar)
{
	(ar);
}
#endif // !_WIN32_WCE_NO_ARCHIVE_SUPPORT


// CmonitorDoc ���

#ifdef _DEBUG
void CmonitorDoc::AssertValid() const
{
	CDocument::AssertValid();
}
#endif //_DEBUG


// CmonitorDoc ����

