#pragma once



// CDataView ������ͼ

class CDataView : public CFormView
{
	DECLARE_DYNCREATE(CDataView)

public:

	CDataView();

	BOOL Create(LPCTSTR, LPCTSTR, DWORD,
		const RECT&, CWnd*, UINT, CCreateContext*);
protected:
      // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};


