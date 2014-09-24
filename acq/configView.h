#pragma once



// ConfigView 窗体视图

class ConfigView : public CFormView
{
	DECLARE_DYNCREATE(ConfigView)

public:
	
	ConfigView(); 
	BOOL Create(LPCTSTR , LPCTSTR , DWORD,
		const RECT&, CWnd*, UINT, CCreateContext*);
protected:
          // 动态创建所使用的受保护的构造函数
	virtual ~ConfigView();

public:
	enum { IDD = IDD_ACQ_FORM };
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
	afx_msg void OnBnClickedButton1();
};


