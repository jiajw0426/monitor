#pragma once
#include "afxwin.h"
#include "../dal/database.h"
#include "MainFrm.h"




// CEditConfigView 窗体视图

class CEditConfigView : public CFormView
{
	DECLARE_DYNCREATE(CEditConfigView)

public:

	CEditConfigView();
   
	BOOL Create(LPCTSTR, LPCTSTR, DWORD,
		const RECT&, CWnd*, UINT, CCreateContext*);
protected:
          // 动态创建所使用的受保护的构造函数
	virtual ~CEditConfigView();
	BOOL validateConfig();

public:
	enum { IDD = IDD_CONFIG_FORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	OConfig*  oconfig; 
	CComboBox serialComBox;
	CComboBox baudComBox;
	CComboBox porityComBox;
	CComboBox databitComBox;
	CComboBox stopbitComBox;
	CComboBox devicenoComBox;
	CEdit registerEdit;
	CEdit nameEdit;
	CEdit LabelEdit;

	CListBox configList;
	virtual void OnInitialUpdate();
protected:
	void initConfigList(void);
	void initSerialPorts(void);
	int initBaud(void);
private:
	void initStopBit(void);
	void initDataBit(void);
	void initPority(void);
	void initDeviceNo(void);
public:
	CComboBox datatypeComboBox;
private:
	void initDataType(void);
public:
	afx_msg void OnBnClickedBtnNewconfig();
	CEdit bytecountEdit;
	afx_msg void OnConfigChangeList();
	CButton btnChange;
	CButton btnDelete;
	afx_msg void OnBnClickedDeleteButton();
	afx_msg void OnBnChangeConfig();
};


