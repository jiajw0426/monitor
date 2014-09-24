// ConfigEditView.cpp : 实现文件
//

#include "stdafx.h"
#include "acq.h"
#include "ConfigEditView.h"


// CConfigEditView 对话框

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
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清除代码。

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

// 注意: 我们添加 IID_IConfigEditView 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {49145BA7-7B37-44B4-A4EE-A7BD2562749F}
static const IID IID_IConfigEditView =
{ 0x49145BA7, 0x7B37, 0x44B4, { 0xA4, 0xEE, 0xA7, 0xBD, 0x25, 0x62, 0x74, 0x9F } };

BEGIN_INTERFACE_MAP(CConfigEditView, CDialog)
	INTERFACE_PART(CConfigEditView, IID_IConfigEditView, Dispatch)
END_INTERFACE_MAP()


// CConfigEditView 消息处理程序
