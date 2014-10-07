// DataView.cpp : 实现文件
//

#include "stdafx.h"
#include "acq.h"
#include "DataView.h"
#include "../dal/database.h"
#include "MainFrm.h"


// CDataView

IMPLEMENT_DYNCREATE(CDataView, CFormView)

CDataView::CDataView()
	: CFormView(CDataView::IDD)
{

}

CDataView::~CDataView()
{
	printf("~CDataView()\n");
}

void CDataView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, 2, startButton);
	DDX_Control(pDX, IDC_BUTTON1, stopButton);
}

BEGIN_MESSAGE_MAP(CDataView, CFormView)
	ON_WM_TIMER()
	ON_BN_CLICKED(2, &CDataView::onStartAcquisition)
	ON_BN_CLICKED(IDC_BUTTON1, &CDataView::onStopAcquisition)
END_MESSAGE_MAP()


// CDataView 诊断

#ifdef _DEBUG
void CDataView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDataView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDataView 消息处理程序
BOOL CDataView::Create(LPCTSTR a , LPCTSTR b , DWORD c,
						const RECT& d, CWnd* e , UINT f, CCreateContext* g){
					return		CFormView::Create(a,b,c,d,e,f,g);
}

void CDataView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	 initControls();
		 
}

void CDataView::initControls(){
	this->stopButton.EnableWindow(FALSE);
    CMainFrame *pMainWnd=(CMainFrame*)AfxGetMainWnd();
	DataBaseTool* dbt=pMainWnd->dbt;
	std::vector<OConfig> configs=dbt->loadConfigs();
	std::vector<OConfig>::iterator it=configs.begin();
	int i=0;
	for(;it!=configs.end();++it){
		try{
			wchar_t str[100];
		 
		   OConfig *tempconfig=(OConfig*)malloc(sizeof(it._Myptr));
		   wsprintf(str,L"%s",  it->name);
		   memcpy(&(tempconfig),&(it._Myptr),sizeof(it._Myptr));
		   CConfigDataControl* control=new CConfigDataControl(i,tempconfig,this);
		   this->controls.push_back(control);
		   i++;
	
	   }
	   catch (std::runtime_error const& err)
	  {
		std::cerr << err.what();
	   }
	}
}

void CDataView::StartAcquisition(){
   this->SetTimer(8,5000,0);
   
}

void CDataView::StopAcquisition(){
	this->KillTimer(8);
}
void CDataView::OnTimer(UINT_PTR nIDEvent)

{
	  g_criSection.Lock();
	  AfxMessageBox(L"寄存器地址必须大于0");
	  g_criSection.Unlock();
}
void CDataView::onStartAcquisition()
{
	this->stopButton.EnableWindow(TRUE);
	this->startButton.EnableWindow(FALSE);
	StartAcquisition();
	
}

void CDataView::onStopAcquisition()
{
	this->stopButton.EnableWindow(FALSE);
	this->startButton.EnableWindow(TRUE);
	StopAcquisition();
}
