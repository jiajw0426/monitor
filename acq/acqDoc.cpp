// acqDoc.cpp : CacqDoc 类的实现
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

// CacqDoc 构造/析构

CacqDoc::CacqDoc()
{
	// TODO: 在此添加一次性构造代码

}

CacqDoc::~CacqDoc()
{
}

BOOL CacqDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}

// CacqDoc 序列化

#ifndef _WIN32_WCE_NO_ARCHIVE_SUPPORT
void CacqDoc::Serialize(CArchive& ar)
{
	(ar);
}
#endif // !_WIN32_WCE_NO_ARCHIVE_SUPPORT


// CacqDoc 诊断

#ifdef _DEBUG
void CacqDoc::AssertValid() const
{
	CDocument::AssertValid();
}
#endif //_DEBUG


// CacqDoc 命令

