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
		int nLicense, nCardType;
		CString strCardNo;
		CCardOperator::DecodeCard(strCard, strCardNo, nLicense, nCardType);
		switch (nCardType)
		{
		case CCardOperator::TYPE_SET:
		{
			int nRuptureCurrent,nPortNum, nChargeTime, nRatedCurrent,nUnitPrice;
			CCardOperator::DecodeSetCard(strCard, strCardNo, nLicense, nCardType, nRuptureCurrent,nPortNum, nChargeTime, nRatedCurrent,nUnitPrice);
			strShow.Format(_T("类型：工具-设置卡\r\nIC卡号：%s\r\n授权码：%d\r\n切断电流：%.02f A\r\n端口数：%d 个\r\n充电时间：%d 分钟\r\n额定电流：%.02f A\r\n单价：%.02f 元\r\n"), strCardNo, nLicense, (float)nRuptureCurrent / (float)g_nINT100,nPortNum, nChargeTime, (float)nRatedCurrent / (float)g_nINT100,(float)nUnitPrice / (float)g_nINT100);
		}
		break;
		case CCardOperator::TYPE_LICENSE:
		{
			CCardOperator::DecodeLicenseCard(strCard, strCardNo, nLicense, nCardType);
			strShow.Format(_T("类型：工具-授权卡\r\nIC卡号：%s\r\n授权码：%d\r\n"), strCardNo, nLicense);
		}
		break;
		case CCardOperator::TYPE_CLEAR:
		{
			int nUsageCount;
			CCardOperator::DecodeClearCard(strCard, strCardNo, nLicense, nCardType, nUsageCount);
			strShow.Format(_T("类型：工具-清除卡\r\nIC卡号：%s\r\n授权码：%d\r\n使用次数：%d\r\n"), strCardNo, nLicense,nUsageCount);
		}
		break;
		case CCardOperator::TYPE_USER_TIME:
		{
			int nUserID, nBalance;
			CCardOperator::DecodeUserCard(strCard,strCardNo,nLicense,nCardType,nUserID,nBalance);
			strShow.Format(_T("类型：会员-时长卡\r\nIC卡号：%s\r\n授权码：%d\r\n客户编号：%d\r\n截止日期：%08X\r\n"), strCardNo,nLicense,nUserID,nBalance);
		}
		break;
		case CCardOperator::TYPE_USER_RECHARGE:
		{
			int nUserID, nBalance;
			CCardOperator::DecodeUserCard(strCard, strCardNo, nLicense, nCardType, nUserID, nBalance);
			strShow.Format(_T("类型：会员-充值卡\r\nIC卡号：%s\r\n授权码：%d\r\n客户编号：%d\r\n金额：%.02f元\r\n"), strCardNo,nLicense, nUserID, (float)nBalance/(float)g_nINT100);
		}
		break;
		default:
			AfxMessageBox(_T("此卡非工具卡或会员卡!"));
			break;
		}
		SetDlgItemText(IDC_EDIT_SHOW, strShow);
	}
	else
		AfxMessageBox(_T("读卡失败!\r\n") + strError);
}
