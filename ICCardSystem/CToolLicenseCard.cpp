// CToolLicenseCard.cpp: 实现文件
//

#include "stdafx.h"
#include "ICCardSystem.h"
#include "CToolLicenseCard.h"
#include "afxdialogex.h"


// CToolLicenseCard 对话框

IMPLEMENT_DYNAMIC(CToolLicenseCard, CDialogEx)

CToolLicenseCard::CToolLicenseCard(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TOOLLICENSECARD, pParent)
{

}

CToolLicenseCard::~CToolLicenseCard()
{
}

void CToolLicenseCard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolLicenseCard, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LICENSECARD, &CToolLicenseCard::OnBnClickedButtonLicensecard)
	ON_EN_CHANGE(IDC_EDIT_LICENSE, &CToolLicenseCard::OnEnChangeEditLicense)
END_MESSAGE_MAP()


// CToolLicenseCard 消息处理程序


BOOL CToolLicenseCard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CToolLicenseCard::OnBnClickedButtonLicensecard()
{
	// TODO: 在此添加控件通知处理程序代码
	int nLicense;
	nLicense = GetDlgItemInt(IDC_EDIT_LICENSE);
	if (!nLicense)
	{
		AfxMessageBox(_T("授权码不能为0!"));
		return;
	}
	CString strCard,strCardNo, strError;
	if (!CCardOperator::ReadCardNo(strCardNo, strError))
	{
		AfxMessageBox(_T("写卡失败!\r\n") + strError);
		return;
	}
	strCard = CCardOperator::EncodeLicenseCard(strCardNo, nLicense, CCardOperator::TYPE_LICENSE);
	if (CCardOperator::WriteCard(strCard, strError, true))
		AfxMessageBox(_T("写卡成功!"));
	else
		AfxMessageBox(_T("写卡失败!\r\n") + strError);
}


void CToolLicenseCard::OnEnChangeEditLicense()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int nLicense;
	nLicense = GetDlgItemInt(IDC_EDIT_LICENSE);
	if(nLicense>0xFFFF)
		SetDlgItemInt(IDC_EDIT_LICENSE,0xFFFF);
}
