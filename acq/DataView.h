#pragma once



// CDataView 窗体视图

class CDataView : public CFormView
{
	DECLARE_DYNCREATE(CDataView)

public:

	CDataView();

	BOOL Create(LPCTSTR, LPCTSTR, DWORD,
		const RECT&, CWnd*, UINT, CCreateContext*);
protected:
      // 动态创建所使用的受保护的构造函数
	virtual ~CDataView();

public:
	enum { IDD = IDD_DIALOG1 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};


