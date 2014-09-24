// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include <AFXPRIV.H>
#include "monitor.h"
#include "MainFrm.h"
#include "windows.h"
#include <../dal/database.h>
#include <../sqlitepp/session.hpp>
#include <../sqlitepp/statement.hpp>
#include <../sqlitepp/into.hpp>
#include <../sqlitepp/use.hpp>


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


     DataBaseTool dbt;
	 monitorView=NULL;
	 configView=NULL;
	 /*
    string_t name=utf("����");
	session db(data);
	//db << "create table employee(id integer primary key, name text, age integer, salary real)";
	// db << "insert into employee values(null, :name, 31, 5500)", use(L"����");
	// db << utf(L"insert into employee values(null, '����', 31, 5500)");

	 employee e;
	statement st(db);
	printf("\n\t-- Employees --\n");
	st << utf(L"select name, age, salary from employee"), into(e.name,utf(L"name")), into(e.age), into(e.salary);
		while ( st.exec() )
		{
		 
			printf("name:%s;age:%d,salary:%f\n",U2G(e.name.c_str()),e.age,e.salary);
		}*/
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


int CMainFrame::showView(int viewId){
	switch(viewId){
		case LOGIN_VIEW:
			return showLoginView();
	}
	return -1;

}

int CMainFrame::showLoginView(){
	if(configView==NULL){
     configView=new ConfigView;
     if(configView==NULL)return FALSE;
	 CDocument* pCurrentDoc =GetActiveDocument();
	 CCreateContext newContext;
	 newContext.m_pNewViewClass = NULL;
	 newContext.m_pNewDocTemplate = NULL;
     newContext.m_pLastView = NULL;
     newContext.m_pCurrentFrame = NULL;
     newContext.m_pCurrentDoc = pCurrentDoc;

	 UINT viewID = AFX_IDW_PANE_FIRST + 1;
     CRect rect(0, 0, 0, 0); // Gets resized later.
	 configView->Create(NULL, _T("AnyWindowName"), WS_CHILD, rect, this, viewID, &newContext);
      configView->SendMessage(WM_INITIALUPDATE, 0, 0);
      //IDV_NEW_VIEW_ID�������ͼ��ID�����ֵ�����ǳ������� 1����������Դ��ͼ��String Table�����ã�����Ϊ:IDV_NEW_VIEW_ID;

	}
    
	 
	
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



