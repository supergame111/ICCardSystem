// CUserCloseCard.cpp: 实现文件
//

#include "stdafx.h"
#include "ICCardSystem.h"
#include "CUserCloseCard.h"
#include "afxdialogex.h"


// CUserCloseCard 对话框

IMPLEMENT_DYNAMIC(CUserCloseCard, CDialogEx)

CUserCloseCard::CUserCloseCard(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USERCLOSECARD, pParent)
{

}

CUserCloseCard::~CUserCloseCard()
{
}

void CUserCloseCard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ID, m_editID);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_IDNO, m_editIDNo);
	DDX_Control(pDX, IDC_EDIT_PHONENO, m_editPhoneNo);
	DDX_Control(pDX, IDC_EDIT_ADDR, m_editAddr);
	DDX_Control(pDX, IDC_EDIT_UNITID, m_editUnitID);
	DDX_Control(pDX, IDC_EDIT_UNITNAME, m_editUnitName);
	DDX_Control(pDX, IDC_EDIT_BALANCE, m_editBalance);
	DDX_Control(pDX, IDC_EDIT_DEPOSIT, m_editDeposit);
	DDX_Control(pDX, IDC_EDIT_AMOUNT, m_editAmount);
}


BEGIN_MESSAGE_MAP(CUserCloseCard, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_READCARD, &CUserCloseCard::OnBnClickedButtonReadcard)
	ON_BN_CLICKED(IDC_BUTTON_CLOSECARD, &CUserCloseCard::OnBnClickedButtonClosecard)
END_MESSAGE_MAP()


// CUserCloseCard 消息处理程序


BOOL CUserCloseCard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CUserCloseCard::OnBnClickedButtonReadcard()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strCard, strError;
	if (CCardOperator::ReadCard(strCard, strError,true))
	{
		int nDeviceID, nUnitID, nCardType, nUserID, nBalance;
		CCardOperator::DecodeUserCard(strCard, nDeviceID, nUnitID, nCardType, nUserID, nBalance);
		if (nDeviceID > 0 && nCardType == CCardOperator::TYPE_USER)
		{
			CString strSql, strBalance,strDeposit,strAmount;
			std::vector<CUser> vec_user;
			strSql.Format(_T("SELECT * FROM User WHERE ID=%d ORDER BY ID"), nUserID);
			m_udb.Select(strSql, vec_user);
			if (vec_user.size() == 1)
			{
				vec_user[0].SetDeviceID(nDeviceID);
				vec_user[0].SetUnitID(nUnitID);
				m_udb.UpdateModifyInfo(vec_user[0]);
				InsertEdit(vec_user[0]);
				m_SelectUser = vec_user[0];
				strBalance.Format(_T("%.02f"), (float)nBalance / (float)g_nINT100);
				m_editBalance.SetWindowText(strBalance);
				strDeposit.Format(_T("%.02f"), (float)vec_user[0].GetDeposit() / (float)g_nINT100);
				m_editDeposit.SetWindowText(strDeposit);
				strAmount.Format(_T("%.02f"), (float)(nBalance+vec_user[0].GetDeposit()) / (float)g_nINT100);
				m_editAmount.SetWindowText(strAmount);
			}
			else
				AfxMessageBox(_T("无客户信息!"));
		}
		else
			AfxMessageBox(_T("此卡非会员卡!"));
	}
	else
		AfxMessageBox(_T("读卡失败!\r\n") + strError);
}


void CUserCloseCard::OnBnClickedButtonClosecard()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strID;
	m_editID.GetWindowText(strID);
	int nID = _ttoi(strID);
	CString strCard, strError;
	if (CCardOperator::ReadCard(strCard, strError))
	{
		int nDeviceID, nUnitID, nCardType, nUserID, nBalance;
		CCardOperator::DecodeUserCard(strCard, nDeviceID, nUnitID, nCardType, nUserID, nBalance);
		if (nDeviceID > 0 && nCardType == CCardOperator::TYPE_USER&&nUserID == nID)
		{
			int nIDRecord;
			std::vector<CRecord> vec_record;
			m_rrdb.Select(_T("SELECT * FROM RefundRecord ORDER BY ID DESC LIMIT 1"), vec_record);
			if (vec_record.size() == 1)
				nIDRecord = vec_record[0].GetID() + 1;
			else
				nIDRecord = 1;
			CRecord recordRefund(nIDRecord, m_SelectUser.GetID(), nBalance, nBalance, 0, m_SelectUser.GetDeposit(),0, _T("退卡_退款"), g_employee.GetID(), _T(""));
			m_rrdb.Insert(recordRefund);//退款
			m_rdrdb.Select(_T("SELECT * FROM ReturnDepositRecord ORDER BY ID DESC LIMIT 1"), vec_record);
			if (vec_record.size() == 1)
				nIDRecord = vec_record[0].GetID() + 1;
			else
				nIDRecord = 1;
			CRecord recordDeposit(nIDRecord, m_SelectUser.GetID(), m_SelectUser.GetDeposit(), m_SelectUser.GetDeposit(), 0,0,0, _T("退卡_退押金"), g_employee.GetID(), _T(""));
			m_rdrdb.Insert(recordDeposit);//退押金
			m_SelectUser.SetState(CUser::STATE_CLOSE);
			m_SelectUser.SetEmployeeIDCloseCard(g_employee.GetID());
			if (m_udb.UpdateCloseCard(m_SelectUser))
			{
				CCardOperator::ClearUserCard(true);
				AfxMessageBox(_T("退卡成功!"));
			}
			else
				AfxMessageBox(_T("退卡失败!"));
		}
		else
			AfxMessageBox(_T("请重新读卡!"));
	}
	else
		AfxMessageBox(_T("退卡失败!\r\n") + strError);
}


void CUserCloseCard::InsertEdit(const CUser & user)
{
	CString str;
	str.Format(_T("%d"), user.GetID());
	m_editID.SetWindowText(str);
	m_editName.SetWindowText(user.GetName());
	m_editIDNo.SetWindowText(user.GetIDNo());
	m_editPhoneNo.SetWindowText(user.GetPhoneNo());
	m_editAddr.SetWindowText(user.GetAddr());
	str.Format(_T("%d"), user.GetUnitID());
	m_editUnitID.SetWindowText(str);
	m_editUnitName.SetWindowText(user.GetUnitName());
}