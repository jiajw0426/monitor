// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "acq.h"
#include <AFXPRIV.H>
#include "MainFrm.h"
#include "windows.h"
#include "../dal/database.h"
#include "../sqlitepp/session.hpp"
#include "../sqlitepp/statement.hpp"
#include "../sqlitepp/into.hpp"
#include "../sqlitepp/use.hpp"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


const DWORD dwAdornmentFlags = 0; // �˳���ť

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	dbt=new DataBaseTool;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	if (!m_wndCommandBar.Create(this) ||
	    !m_wndCommandBar.InsertMenuBar(IDR_MAINFRAME) ||
	    !m_wndCommandBar.AddAdornments(dwAdornmentFlags))
	{
		TRACE0("δ�ܴ��� CommandBar\n");
		return -1;      // δ�ܴ���
	}

	m_wndCommandBar.SetBarStyle(m_wndCommandBar.GetBarStyle() | CBRS_SIZE_FIXED);

    CView* old=this->GetActiveView();
   old->MoveWindow(0,0,0,0,1);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
  
	return TRUE;
}


// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}
#endif //_DEBUG

// CMainFrame ��Ϣ�������

CView* CMainFrame::CreateView(CRuntimeClass* clazz){
	 
	 CView* newView=(CView*)clazz->CreateObject();

 
	 CDocument* pCurrentDoc =GetActiveDocument();
	 CCreateContext newContext;
	 newContext.m_pNewViewClass = NULL;
	 newContext.m_pNewDocTemplate = NULL;
     newContext.m_pLastView = NULL;
     newContext.m_pCurrentFrame = NULL;
     newContext.m_pCurrentDoc = pCurrentDoc;
     UINT viewID = AFX_IDW_PANE_FIRST + 1;
   	 
	 newView->Create(NULL, _T("AnyWindowName"), WS_CHILD, CFrameWnd::rectDefault, this, viewID, &newContext);
     newView->SendMessage(WM_INITIALUPDATE, 0, 0);
	 return newView;
	 
 
}