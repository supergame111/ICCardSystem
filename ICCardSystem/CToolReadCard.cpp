// CToolReadCard.cpp: 实现文件
//

#include "stdafx.h"
#include "ICCardSystem.h"
#include "CToolReadCard.h"
#include "afxdialogex.h"


// CToolReadCard 对话框

IMPLEMENT_DYNAMIC(CToolReadCard, CDialogEx)

CToolReadCard::CToolReadCard(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TOOLREADCARD, pParent)
{

}

CToolReadCard::~CToolReadCard()
{
}

void CToolReadCard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolReadCard, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_READCARD, &CToolReadCard::OnBnClickedButtonReadcard)
END_MESSAGE_MAP()


// CToolReadCard 消息处理程序


BOOL CToolReadCard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CToolReadCard::OnBnClickedButtonReadcard()
{
	// TODO: 在此添加控件通知处理程序代码
	SetDlgItemText(IDC_EDIT_SHOW, _T(""));
	CString strCard, strError,strShow;
	if (CCardOperator::ReadCard(strCard, strError,true))
	{
		int nCardNo, nLicense, nCardType;
		CCardOperator::DecodeCard(strCard, nCardNo, nLicense, nCardType);
		if(nCardNo)
			AfxMessageBox(_T("此卡非工具卡!"));
		else
		{
			switch (nCardType)
			{
			case CCardOperator::TYPE_SET:
			{
				int nPortNum, nChargeTime, nUnitPrice;
				CCardOperator::DecodeSetCard(strCard, nCardNo, nLicense, nCardType, nPortNum, nChargeTime, nUnitPrice);
				strShow.Format(_T("类型：设置卡\r\n授权码：%d\r\n端口数：%d 个\r\n充电时间：%d 分钟\r\n单价：%.02f 元\r\n"),nLicense,nPortNum,nChargeTime,(float)nUnitPrice/(float)g_nINT100);
			}
			break;
			case CCardOperator::TYPE_LICENSE:
			{
				CCardOperator::DecodeLicenseCard(strCard, nCardNo, nLicense, nCardType);
				strShow.Format(_T("类型：授权卡\r\n授权码：%d\r\n"),nLicense);
			}
			break;
			default:
				AfxMessageBox(_T("错误工具卡!"));
				break;
			}
			SetDlgItemText(IDC_EDIT_SHOW, strShow);
		}
	}
	else
		AfxMessageBox(_T("读卡失败!\r\n") + strError);
}
