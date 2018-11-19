// CToolTestCard.cpp: 实现文件
//

#include "stdafx.h"
#include "ICCardSystem.h"
#include "CToolTestCard.h"
#include "afxdialogex.h"


// CToolTestCard 对话框

IMPLEMENT_DYNAMIC(CToolTestCard, CDialogEx)

CToolTestCard::CToolTestCard(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TOOLTESTCARD, pParent)
{

}

CToolTestCard::~CToolTestCard()
{
}

void CToolTestCard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolTestCard, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TESTCARD, &CToolTestCard::OnBnClickedButtonTestcard)
END_MESSAGE_MAP()


// CToolTestCard 消息处理程序


BOOL CToolTestCard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CToolTestCard::OnBnClickedButtonTestcard()
{
	// TODO: 在此添加控件通知处理程序代码
	int nUnitID;
	nUnitID = GetDlgItemInt(IDC_EDIT_UNITID);
	CString strCard, strError;
	strCard = CCardOperator::EncodeTestCard(0x00000000, nUnitID, CCardOperator::TYPE_TEST);
	if (CCardOperator::WriteCard(strCard, strError,true))
		AfxMessageBox(_T("写卡成功!"));
	else
		AfxMessageBox(_T("写卡失败!\r\n") + strError);
}
