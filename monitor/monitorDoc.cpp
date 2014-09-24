// monitorDoc.cpp : CmonitorDoc 类的实现
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

// CmonitorDoc 构造/析构

CmonitorDoc::CmonitorDoc()
{
	// TODO: 在此添加一次性构造代码

}

CmonitorDoc::~CmonitorDoc()
{
}

BOOL CmonitorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}

// CmonitorDoc 序列化

#ifndef _WIN32_WCE_NO_ARCHIVE_SUPPORT
void CmonitorDoc::Serialize(CArchive& ar)
{
	(ar);
}
#endif // !_WIN32_WCE_NO_ARCHIVE_SUPPORT


// CmonitorDoc 诊断

#ifdef _DEBUG
void CmonitorDoc::AssertValid() const
{
	CDocument::AssertValid();
}
#endif //_DEBUG


// CmonitorDoc 命令

