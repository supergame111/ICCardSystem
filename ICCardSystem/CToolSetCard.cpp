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
	ON_EN_CHANGE(IDC_EDIT_LICENSE, &CToolSetCard::OnEnChangeEditLicense)
	ON_EN_CHANGE(IDC_EDIT_RUPTURECURRENT, &CToolSetCard::OnEnChangeEditRupturecurrent)
	ON_EN_CHANGE(IDC_EDIT_PORTNUM, &CToolSetCard::OnEnChangeEditPortnum)
	ON_EN_CHANGE(IDC_EDIT_CHARGETIME, &CToolSetCard::OnEnChangeEditChargetime)
	ON_EN_CHANGE(IDC_EDIT_RATEDCURRENT, &CToolSetCard::OnEnChangeEditRatedcurrent)
	ON_EN_CHANGE(IDC_EDIT_UNITPRICE, &CToolSetCard::OnEnChangeEditUnitprice)
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
	CString strRuptureCurrent,strRatedCurrent,strUnitPrice;
	int nLicense, nRuptureCurrent,nPortNum,nChargeTime, nRatedCurrent,nUnitPrice;
	nLicense = GetDlgItemInt(IDC_EDIT_LICENSE);
	GetDlgItemText(IDC_EDIT_RUPTURECURRENT, strRuptureCurrent);
	nRuptureCurrent = int(_ttof(strRuptureCurrent)*(float)g_nINT100+0.5);
	nPortNum = GetDlgItemInt(IDC_EDIT_PORTNUM);
	nChargeTime = GetDlgItemInt(IDC_EDIT_CHARGETIME);
	GetDlgItemText(IDC_EDIT_RATEDCURRENT, strRatedCurrent);
	nRatedCurrent = int(_ttof(strRatedCurrent)*(float)g_nINT100+0.5);
	GetDlgItemText(IDC_EDIT_UNITPRICE,strUnitPrice);
	nUnitPrice = int(_ttof(strUnitPrice)*(float)g_nINT100+0.5);
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
	strCard = CCardOperator::EncodeSetCard(strCardNo, nLicense, CCardOperator::TYPE_SET, nRuptureCurrent,nPortNum,nChargeTime, nRatedCurrent,nUnitPrice);
	if (CCardOperator::WriteCard(strCard, strError,true))
		AfxMessageBox(_T("写卡成功!"));
	else
		AfxMessageBox(_T("写卡失败!\r\n") + strError);
}


void CToolSetCard::OnEnChangeEditLicense()
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


void CToolSetCard::OnEnChangeEditRupturecurrent()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strRuptureCurrent;
	int nRuptureCurrent;
	GetDlgItemText(IDC_EDIT_RUPTURECURRENT, strRuptureCurrent);
	nRuptureCurrent = int(_ttof(strRuptureCurrent)*(float)g_nINT100+0.5);
	if (nRuptureCurrent > 0xFF)
		SetDlgItemText(IDC_EDIT_RUPTURECURRENT, _T("2.55"));
}


void CToolSetCard::OnEnChangeEditPortnum()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int nPortNum;
	nPortNum = GetDlgItemInt(IDC_EDIT_PORTNUM);
	if (nPortNum > 0xFF)
		SetDlgItemInt(IDC_EDIT_PORTNUM, 0xFF);
}


void CToolSetCard::OnEnChangeEditChargetime()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	int nChargeTime;
	nChargeTime = GetDlgItemInt(IDC_EDIT_CHARGETIME);
	if (nChargeTime > 0xFFFF)
		SetDlgItemInt(IDC_EDIT_CHARGETIME, 0xFFFF);
}


void CToolSetCard::OnEnChangeEditRatedcurrent()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strRatedCurrent;
	int nRatedCurrent;
	GetDlgItemText(IDC_EDIT_RATEDCURRENT, strRatedCurrent);
	nRatedCurrent = int(_ttof(strRatedCurrent)*(float)g_nINT100+0.5);
	if (nRatedCurrent > 0xFFFF)
		SetDlgItemText(IDC_EDIT_RATEDCURRENT, _T("655.35"));
}


void CToolSetCard::OnEnChangeEditUnitprice()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strUnitPrice;
	int nUnitPrice;
	GetDlgItemText(IDC_EDIT_UNITPRICE, strUnitPrice);
	nUnitPrice = int(_ttof(strUnitPrice)*(float)g_nINT100+0.5);
	if (nUnitPrice > 0xFFFF)
		SetDlgItemText(IDC_EDIT_UNITPRICE, _T("655.35"));
}
