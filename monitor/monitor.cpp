// monitor.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "monitor.h"
#include "MainFrm.h"

#include "monitorDoc.h"
#include "monitorView.h"
#include "ConfigView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmonitorApp

BEGIN_MESSAGE_MAP(CmonitorApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CmonitorApp::OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	ON_COMMAND(ID_LOGIN, &CmonitorApp::OnLogin)
END_MESSAGE_MAP()



// CmonitorApp ����
CmonitorApp::CmonitorApp()
	: CWinApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CmonitorApp ����
CmonitorApp theApp;

// CmonitorApp ��ʼ��

BOOL CmonitorApp::InitInstance()
{

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
#ifdef WIN32_PLATFORM_PSPC
	CDocListDocTemplate* pDocTemplate;
	pDocTemplate = new CDocListDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CmonitorDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CmonitorView));
	AddDocTemplate(pDocTemplate);

	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	ParseCommandLine(cmdInfo);

	pDocTemplate->ShowDocList();	
	
	// ����ĵ��б���û���ļ���������һ�����ļ���
	CDocList* pDocList = pDocTemplate->m_pWndDocList;	
	if (pDocList->GetItemCount() == 0) 
	{
		pDocList->OnClose();
		OnFileNew();
	}
#else
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CmonitorDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CmonitorView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
#endif // WIN32_PLATFORM_PSPC

#ifndef WIN32_PLATFORM_PSPC
	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
#endif // !WIN32_PLATFORM_PSPC

#ifndef WIN32_PLATFORM_PSPC
	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
#endif // !WIN32_PLATFORM_PSPC
	return TRUE;
}


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
#ifdef _DEVICE_RESOLUTION_AWARE
	afx_msg void OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/);
#endif
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;	// ���ǽ��������õ��ؼ������򷵻� TRUE
			// �쳣: OCX ����ҳӦ���� FALSE
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
#ifdef _DEVICE_RESOLUTION_AWARE
	ON_WM_SIZE()
#endif
	 
END_MESSAGE_MAP()

#ifdef _DEVICE_RESOLUTION_AWARE
void CAboutDlg::OnSize(UINT /*nType*/, int /*cx*/, int /*cy*/)
{
	if (AfxIsDRAEnabled())
    	{
		DRA::RelayoutDialog(
			AfxGetResourceHandle(), 
			this->m_hWnd, 
			DRA::GetDisplayMode() != DRA::Portrait ? MAKEINTRESOURCE(IDD_ABOUTBOX_WIDE) : MAKEINTRESOURCE(IDD_ABOUTBOX));
	}
}
#endif

// �������жԻ����Ӧ�ó�������
void CmonitorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}



void CmonitorApp::OnLogin()
{
	CMainFrame *m_pMainWnd =(CMainFrame *)AfxGetMainWnd();
	m_pMainWnd->showView(LOGIN_VIEW);

	CView* pActiveView = ((CFrameWnd*) m_pMainWnd)->GetActiveView();

	CView* pNewView = m_pMainWnd->configView;
   
	 #ifndef _WIN32
   UINT temp = ::GetWindowWord(pActiveView->m_hWnd, GWW_ID);
   ::SetWindowWord(pActiveView->m_hWnd, GWW_ID, ::GetWindowWord(pNewView->m_hWnd, GWW_ID));
   ::SetWindowWord(pNewView->m_hWnd, GWW_ID, temp);
   #else
   UINT temp = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);
   ::SetWindowLong(pActiveView->m_hWnd, GWL_ID, ::GetWindowLong(pNewView->m_hWnd, GWL_ID));
   ::SetWindowLong(pNewView->m_hWnd, GWL_ID, temp);
   #endif

   pActiveView->ShowWindow(SW_HIDE);
   pNewView->ShowWindow(SW_SHOW);
   ((CFrameWnd*) m_pMainWnd)->SetActiveView(pNewView);
   ((CFrameWnd*) m_pMainWnd)->RecalcLayout();
   pNewView->Invalidate();
 

}
