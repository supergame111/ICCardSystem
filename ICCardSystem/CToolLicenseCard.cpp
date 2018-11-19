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
	CString strCard, strError;
	strCard = CCardOperator::EncodeLicenseCard(0x00000000, nLicense, CCardOperator::TYPE_LICENSE);
	if (CCardOperator::WriteCard(strCard, strError, true))
		AfxMessageBox(_T("写卡成功!"));
	else
		AfxMessageBox(_T("写卡失败!\r\n") + strError);
}
