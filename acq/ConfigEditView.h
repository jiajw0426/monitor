#pragma once


// CConfigEditView �Ի���

class CConfigEditView : public CDialog
{
	DECLARE_DYNAMIC(CConfigEditView)

public:
	CConfigEditView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CConfigEditView();

	virtual void OnFinalRelease();

// �Ի�������
	enum { IDD = IDD_ACQ_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};
