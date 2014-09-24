#pragma once


// CConfigEditView 对话框

class CConfigEditView : public CDialog
{
	DECLARE_DYNAMIC(CConfigEditView)

public:
	CConfigEditView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CConfigEditView();

	virtual void OnFinalRelease();

// 对话框数据
	enum { IDD = IDD_ACQ_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
