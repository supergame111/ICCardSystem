// CToolClearCard.cpp: 实现文件
//

#include "stdafx.h"
#include "ICCardSystem.h"
#include "CToolClearCard.h"
#include "afxdialogex.h"


// CToolClearCard 对话框

IMPLEMENT_DYNAMIC(CToolClearCard, CDialogEx)

CToolClearCard::CToolClearCard(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TOOLCLEARCARD, pParent)
{

}

CToolClearCard::~CToolClearCard()
{
}

void CToolClearCard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolClearCard, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLEARCARD, &CToolClearCard::OnBnClickedButtonClearcard)
	ON_EN_CHANGE(IDC_EDIT_LICENSE, &CToolClearCard::OnEnChangeEditLicense)
	ON_EN_CHANGE(IDC_EDIT_USAGECOUNT, &CToolClearCard::OnEnChangeEditUsagecount)
END_MESSAGE_MAP()


// CToolClearCard 消息处理程序


BOOL CToolClearCard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetDlgItemInt(IDC_EDIT_LICENSE, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CToolClearCard::OnBnClickedButtonClearcard()
{
	// TODO: 在此添加控件通知处理程序代码
	int nLicense,nUsageCount;
	nLicense = GetDlgItemInt(IDC_EDIT_LICENSE);
	nUsageCount= GetDlgItemInt(IDC_EDIT_USAGECOUNT);
	CString strCard, strCardNo, strError;
	if (!CCardOperator::ReadCardNo(strCardNo, strError))
	{
		AfxMessageBox(_T("写卡失败!\r\n") + strError);
		return;
	}
	strCard = CCardOperator::EncodeClearCard(strCardNo, nLicense, CCardOperator::TYPE_CLEAR,nUsageCount);
	if (CCardOperator::WriteCard(strCard, strError, true))
		AfxMessageBox(_T("写卡成功!"));
	else
		AfxMessageBox(_T("写卡失败!\r\n") + strError);
}


void CToolClearCard::OnEnChangeEditLicense()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int nLicense;
	nLicense = GetDlgItemInt(IDC_EDIT_LICENSE);
	if (nLicense > 0xFFFF)
		SetDlgItemInt(IDC_EDIT_LICENSE, 0xFFFF);
}


void CToolClearCard::OnEnChangeEditUsagecount()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int nUsageCount;
	nUsageCount = GetDlgItemInt(IDC_EDIT_USAGECOUNT);
	if (nUsageCount > 0xFFFF)
		SetDlgItemInt(IDC_EDIT_USAGECOUNT, 0xFFFF);
}
