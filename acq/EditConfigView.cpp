// EditConfigView.cpp : 实现文件
//

#include "stdafx.h"
#include "acq.h"
#include "EditConfigView.h"
#include <math.h> 



// CEditConfigView

IMPLEMENT_DYNCREATE(CEditConfigView, CFormView)

CEditConfigView::CEditConfigView()
	: CFormView(CEditConfigView::IDD)
{
	oconfig=new OConfig;
	oconfig->baud=9600;
	oconfig->databit=8;
	oconfig->stopbit=1;
	oconfig->pority=L"None";
	oconfig->port=L"COM1";
	oconfig->bytecount=1;
	oconfig->deviceno=1;
	oconfig->reg=1;
}

CEditConfigView::~CEditConfigView()
{
}

void CEditConfigView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, serialComBox);
	DDX_Text(pDX, IDC_COMBO2, oconfig->port);


	DDX_Control(pDX, IDC_COMBO3, baudComBox);
	DDX_Text(pDX, IDC_COMBO3, oconfig->baud);



	DDX_Control(pDX, IDC_COMBO4, porityComBox);
	DDX_Text(pDX, IDC_COMBO4, oconfig->pority);

	DDX_Control(pDX, IDC_COMBO5, databitComBox);
	DDX_Text(pDX, IDC_COMBO5, oconfig->databit);

	DDX_Control(pDX, IDC_COMBO6, stopbitComBox);
	DDX_Text(pDX, IDC_COMBO6, oconfig->stopbit);

	DDX_Control(pDX, IDC_COMBO7, devicenoComBox);
	DDX_Text(pDX, IDC_COMBO7, oconfig->deviceno);

	DDX_Control(pDX, IDC_EDIT7, registerEdit);
	DDX_Text(pDX, IDC_EDIT7, oconfig->reg);

	DDX_Control(pDX, IDC_EDIT4, nameEdit);
	DDX_Text(pDX, IDC_EDIT4, oconfig->name);

	DDX_Control(pDX, IDC_EDIT5, LabelEdit);
	DDX_Text(pDX, IDC_EDIT5, oconfig->label);

	DDX_Control(pDX, IDC_LIST1, configList);

	DDX_Control(pDX, IDC_COMBO8, datatypeComboBox);
	DDX_Text(pDX, IDC_COMBO8, oconfig->datatype);

	DDX_Control(pDX, IDC_EDIT8, bytecountEdit);
	DDX_Text(pDX, IDC_EDIT8, oconfig->bytecount);
	DDX_Control(pDX, IDC_BTN_CHANGE_CONFIG, btnChange);
	DDX_Control(pDX, IDC_BUTTON1, btnDelete);
}

BEGIN_MESSAGE_MAP(CEditConfigView, CFormView)

	ON_BN_CLICKED(IDC_BTN_NEWCONFIG, &CEditConfigView::OnBnClickedBtnNewconfig)
	ON_LBN_SELCHANGE(IDC_LIST1, &CEditConfigView::OnConfigChangeList)
	ON_BN_CLICKED(IDC_BUTTON1, &CEditConfigView::OnBnClickedDeleteButton)
	ON_BN_CLICKED(IDC_BTN_CHANGE_CONFIG, &CEditConfigView::OnBnChangeConfig)
END_MESSAGE_MAP()


// CEditConfigView 诊断

#ifdef _DEBUG
void CEditConfigView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CEditConfigView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CEditConfigView 消息处理程序
BOOL CEditConfigView::Create(LPCTSTR a , LPCTSTR b , DWORD c,
						const RECT& d, CWnd* e , UINT f, CCreateContext* g){
					return		CFormView::Create(a,b,c,d,e,f,g);
}


void CEditConfigView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	initConfigList();
	initSerialPorts();
	initBaud();
	initStopBit();
	initPority();
	initDataBit();
	initDeviceNo();
	initDataType();

	
}

void CEditConfigView::initConfigList(void)
{
	configList.ResetContent();
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
		   configList.AddString((LPCTSTR)str);
		   configList.SetItemData(i++,(DWORD)tempconfig->id);
		 
	
	   }
	   catch (std::runtime_error const& err)
	  {
		std::cerr << err.what();
	   }
	}
	btnChange.EnableWindow(false);
	btnDelete.EnableWindow(false);
	 
}

void CEditConfigView::initSerialPorts(void)
{

	
	for(int i=0;i<10;i++){
		wchar_t str[10];

      wsprintf(str,L"COM%d",i);
	 serialComBox.AddString(LPTSTR(str));
	}
}

int CEditConfigView::initBaud(void)
{
	 baudComBox.AddString(LPTSTR(L"110"));
	 for(int  i=0;i<10;i++){
		wchar_t str[10];
      int d=pow(2,i);
	  long b=d*300;
      wsprintf(str,L"%ld",b);
	  baudComBox.AddString(LPTSTR(str));
	}
	  baudComBox.AddString(LPTSTR(L"115200"));
	 
	return 0;
}

void CEditConfigView::initStopBit(void)
{
	stopbitComBox.AddString(LPTSTR(L"1"));
	stopbitComBox.AddString(LPTSTR(L"2"));
}

void CEditConfigView::initDataBit(void)
{
	databitComBox.AddString(LPTSTR(L"5"));
	databitComBox.AddString(LPTSTR(L"6"));
	databitComBox.AddString(LPTSTR(L"7"));
	databitComBox.AddString(LPTSTR(L"8"));
}

void CEditConfigView::initPority(void)
{
    porityComBox.AddString(LPTSTR(L"None"));
	porityComBox.AddString(LPTSTR(L"Odd"));
	porityComBox.AddString(LPTSTR(L"Even"));
	porityComBox.AddString(LPTSTR(L"Mark"));
	porityComBox.AddString(LPTSTR(L"Space"));
}

void CEditConfigView::initDeviceNo(void)
{
	for(int i=1;i<=32;i++){
		wchar_t str[10];

      wsprintf(str,L"%d",i);
	 devicenoComBox.AddString(LPTSTR(str));
	}
    

}

void CEditConfigView::initDataType(void)
{
  datatypeComboBox.AddString(LPTSTR(L"int"));
  datatypeComboBox.AddString(LPTSTR(L"long"));
  datatypeComboBox.AddString(LPTSTR(L"double"));
  datatypeComboBox.AddString(LPTSTR(L"float"));
  datatypeComboBox.AddString(LPTSTR(L"string"));
  
}

void CEditConfigView::OnBnClickedBtnNewconfig()
{
	UpdateData(TRUE);
	//oconfig->dump();
	if(validateConfig()){
	CMainFrame *pMainWnd=(CMainFrame*)AfxGetMainWnd();
	DataBaseTool* dbt=pMainWnd->dbt;
	dbt->addConfig(*oconfig);
	initConfigList();
	}
	
}

void CEditConfigView::OnConfigChangeList()
{
	int i=configList.GetCurSel();
	
	DWORD configid=configList.GetItemData(i);
    CMainFrame *pMainWnd=(CMainFrame*)AfxGetMainWnd();
	DataBaseTool* dbt=pMainWnd->dbt;
	oconfig=dbt->loadConfigById((int)configid);
	UpdateData(FALSE);
	btnChange.EnableWindow(TRUE);
	btnDelete.EnableWindow(TRUE);
}

void CEditConfigView::OnBnClickedDeleteButton()
{
	 int i=configList.GetCurSel();
	CMainFrame *pMainWnd=(CMainFrame*)AfxGetMainWnd();
	DWORD configid=configList.GetItemData(i);
	DataBaseTool* dbt=pMainWnd->dbt;
	dbt->delConfig((int)configid);
	initConfigList();
	 
}

void CEditConfigView::OnBnChangeConfig()
{
	UpdateData(TRUE);
	//oconfig->dump();
	if(validateConfig()){

	CMainFrame *pMainWnd=(CMainFrame*)AfxGetMainWnd();
	DataBaseTool* dbt=pMainWnd->dbt;
	dbt->updateConfig(*oconfig);
		}
}
BOOL CEditConfigView::validateConfig(){
	if(oconfig->name.IsEmpty()){
	   AfxMessageBox(L"'指标名'不能为空!");
	   return FALSE;
	}
	if(oconfig->label.IsEmpty()){
	   AfxMessageBox(L"'描述'不能为空!");
	   return FALSE;
	}
	if(oconfig->reg<=0){
	   AfxMessageBox(L"寄存器地址必须大于0");
	   return FALSE;
	}
	return TRUE;
}