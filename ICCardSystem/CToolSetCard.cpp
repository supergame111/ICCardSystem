// CToolSetCard.cpp: 实现文件
//

#include "stdafx.h"
#include "ICCardSystem.h"
#include "CToolSetCard.h"
#include "afxdialogex.h"


// CToolSetCard 对话框

IMPLEMENT_DYNAMIC(CToolSetCard, CDialogEx)

CToolSetCard::CToolSetCard(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TOOLSETCARD, pParent)
{

}

CToolSetCard::~CToolSetCard()
{
}

void CToolSetCard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolSetCard, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SETCARD, &CToolSetCard::OnBnClickedButtonSetcard)
END_MESSAGE_MAP()


// CToolSetCard 消息处理程序


BOOL CToolSetCard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CToolSetCard::OnBnClickedButtonSetcard()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strUnitPrice;
	int nLicense,nPortNum,nChargeTime,nUnitPrice;
	nLicense = GetDlgItemInt(IDC_EDIT_LICENSE);
	nPortNum = GetDlgItemInt(IDC_EDIT_PORTNUM);
	nChargeTime = GetDlgItemInt(IDC_EDIT_CHARGETIME);
	GetDlgItemText(IDC_EDIT_UNITPRICE,strUnitPrice);
	nUnitPrice = int(_ttof(strUnitPrice)*(float)g_nINT100);
	CString strCard, strError;
	strCard = CCardOperator::EncodeSetCard(0x00000000, nLicense, CCardOperator::TYPE_SET,nPortNum,nChargeTime,nUnitPrice);
	if (CCardOperator::WriteCard(strCard, strError,true))
		AfxMessageBox(_T("写卡成功!"));
	else
		AfxMessageBox(_T("写卡失败!\r\n") + strError);
}
