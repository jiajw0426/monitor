// acqDoc.cpp : CacqDoc ���ʵ��
//

#include "stdafx.h"
#include "acq.h"

#include "acqDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CacqDoc

IMPLEMENT_DYNCREATE(CacqDoc, CDocument)

BEGIN_MESSAGE_MAP(CacqDoc, CDocument)
END_MESSAGE_MAP()

// CacqDoc ����/����

CacqDoc::CacqDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CacqDoc::~CacqDoc()
{
}

BOOL CacqDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}

// CacqDoc ���л�

#ifndef _WIN32_WCE_NO_ARCHIVE_SUPPORT
void CacqDoc::Serialize(CArchive& ar)
{
	(ar);
}
#endif // !_WIN32_WCE_NO_ARCHIVE_SUPPORT


// CacqDoc ���

#ifdef _DEBUG
void CacqDoc::AssertValid() const
{
	CDocument::AssertValid();
}
#endif //_DEBUG


// CacqDoc ����

