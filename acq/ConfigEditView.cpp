// ConfigEditView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "acq.h"
#include "ConfigEditView.h"


// CConfigEditView �Ի���

IMPLEMENT_DYNAMIC(CConfigEditView, CDialog)

CConfigEditView::CConfigEditView(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigEditView::IDD, pParent)
{

	EnableAutomation();

}

CConfigEditView::~CConfigEditView()
{
}

void CConfigEditView::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

	CDialog::OnFinalRelease();
}

void CConfigEditView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfigEditView, CDialog)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CConfigEditView, CDialog)
END_DISPATCH_MAP()

// ע��: ������� IID_IConfigEditView ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {49145BA7-7B37-44B4-A4EE-A7BD2562749F}
static const IID IID_IConfigEditView =
{ 0x49145BA7, 0x7B37, 0x44B4, { 0xA4, 0xEE, 0xA7, 0xBD, 0x25, 0x62, 0x74, 0x9F } };

BEGIN_INTERFACE_MAP(CConfigEditView, CDialog)
	INTERFACE_PART(CConfigEditView, IID_IConfigEditView, Dispatch)
END_INTERFACE_MAP()


// CConfigEditView ��Ϣ�������
