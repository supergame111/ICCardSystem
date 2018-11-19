// CUserReturnDeposit.cpp: 实现文件
//

#include "stdafx.h"
#include "ICCardSystem.h"
#include "CUserReturnDeposit.h"
#include "afxdialogex.h"


// CUserReturnDeposit 对话框

IMPLEMENT_DYNAMIC(CUserReturnDeposit, CDialogEx)

CUserReturnDeposit::CUserReturnDeposit(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USERRETURNDEPOSIT, pParent)
	, m_nDeposit(0)
{

}

CUserReturnDeposit::~CUserReturnDeposit()
{
}

void CUserReturnDeposit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ID, m_editID);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_IDNO, m_editIDNo);
	DDX_Control(pDX, IDC_EDIT_PHONENO, m_editPhoneNo);
	DDX_Control(pDX, IDC_EDIT_ADDR, m_editAddr);
	DDX_Control(pDX, IDC_EDIT_LICENSE, m_editLicense);
	DDX_Control(pDX, IDC_EDIT_UNITNAME, m_editUnitName);
	DDX_Control(pDX, IDC_EDIT_DEPOSIT, m_editDeposit);
	DDX_Control(pDX, IDC_EDIT_AMOUNT, m_editAmount);
	DDX_Control(pDX, IDC_EDIT_DEPOSITNEW, m_editDepositNew);
	DDX_Control(pDX, IDC_EDIT_NOTEINFO, m_editNoteInfo);
}


BEGIN_MESSAGE_MAP(CUserReturnDeposit, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_READCARD, &CUserReturnDeposit::OnBnClickedButtonReadcard)
	ON_BN_CLICKED(IDC_BUTTON_RETURNDEPOSIT, &CUserReturnDeposit::OnBnClickedButtonReturndeposit)
	ON_EN_CHANGE(IDC_EDIT_AMOUNT, &CUserReturnDeposit::OnEnChangeEditAmount)
END_MESSAGE_MAP()


// CUserReturnDeposit 消息处理程序


BOOL CUserReturnDeposit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CUserReturnDeposit::OnBnClickedButtonReadcard()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strCard, strError;
	if (CCardOperator::ReadCard(strCard, strError,true))
	{
		int nCardNo, nLicense, nCardType, nUserID, nBalance;
		CCardOperator::DecodeUserCard(strCard, nCardNo, nLicense, nCardType, nUserID, nBalance);
		if (nCardNo > 0 && nCardType == CCardOperator::TYPE_USER)
		{
			CString strSql;
			std::vector<CUser> vec_user;
			strSql.Format(_T("SELECT * FROM User WHERE ID=%d ORDER BY ID"), nUserID);
			m_udb.Select(strSql, vec_user);
			if (vec_user.size() == 1)
			{
				//大修改vec_user[0].SetCardNo(nCardNo);
				vec_user[0].SetLicense(nLicense);
				m_udb.UpdateModifyInfo(vec_user[0]);
				GetDeposit(vec_user[0]);
				InsertEdit(vec_user[0]);
				m_SelectUser = vec_user[0];
				m_editAmount.SetWindowText(_T("0"));
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


void CUserReturnDeposit::OnBnClickedButtonReturndeposit()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strID, strAmount, strNoteInfo;
	m_editID.GetWindowText(strID);
	m_editAmount.GetWindowText(strAmount);
	m_editNoteInfo.GetWindowText(strNoteInfo);
	int nID = _ttoi(strID);
	int nAmount = _ttoi(strAmount)*g_nINT100;
	if (nAmount == 0)
	{
		AfxMessageBox(_T("退款金额不能为0!"));
		return;
	}
	CString strCard, strError;
	if (CCardOperator::ReadCard(strCard, strError))
	{
		int nCardNo, nLicense, nCardType, nUserID, nBalance;
		CCardOperator::DecodeUserCard(strCard, nCardNo, nLicense, nCardType, nUserID, nBalance);
		if (nCardNo > 0 && nCardType == CCardOperator::TYPE_USER&&nUserID == nID)
		{
			int nIDRecord;
			std::vector<CRecord> vec_record;
			m_rdrdb.Select(_T("SELECT * FROM ReturnDepositRecord ORDER BY ID DESC LIMIT 1"), vec_record);
			if (vec_record.size() == 1)
				nIDRecord = vec_record[0].GetID() + 1;
			else
				nIDRecord = 1;
			GetDeposit(m_SelectUser);
			CRecord record(nIDRecord, m_SelectUser.GetID(), m_nDeposit, nAmount, m_nDeposit - nAmount, m_nDeposit - nAmount,0, strNoteInfo, g_employee.GetID(), _T(""));
			if (m_rdrdb.Insert(record))
			{
				OnBnClickedButtonReadcard();
				AfxMessageBox(_T("退押金成功!"));
			}
			else
				AfxMessageBox(_T("退押金失败!"));
		}
		else
			AfxMessageBox(_T("请重新读卡!"));
	}
	else
		AfxMessageBox(_T("退押金失败!\r\n") + strError);
}


void CUserReturnDeposit::OnEnChangeEditAmount()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strDeposit, strAmount;
	float fDeposit, fAmount;
	m_editDeposit.GetWindowText(strDeposit);
	m_editAmount.GetWindowText(strAmount);
	fDeposit = (float)_ttof(strDeposit);
	fAmount = (float)_ttof(strAmount);
	if (fAmount > fDeposit)
	{
		fAmount = fDeposit;
		strAmount.Format(_T("%d"), (int)fAmount);
		m_editAmount.SetWindowText(strAmount);
		m_editAmount.SetSel(strAmount.GetLength(), strAmount.GetLength());
	}
	fDeposit -= fAmount;
	strDeposit.Format(_T("%.2f"), fDeposit);
	m_editDepositNew.SetWindowText(strDeposit);
}


void CUserReturnDeposit::GetDeposit(const CUser & user)
{
	CString strSql;
	std::vector<CRecord> vec_record;
	strSql.Format(_T("SELECT * FROM ReturnDepositRecord WHERE UserID=%d ORDER BY Time DESC LIMIT 1"), user.GetID());
	m_rdrdb.Select(strSql, vec_record);
	if (vec_record.size() == 1)
		m_nDeposit = vec_record[0].GetAmountNew();
	//大修改else
		//大修改m_nDeposit = user.GetDeposit();
}


void CUserReturnDeposit::InsertEdit(const CUser & user)
{
	CString str;
	str.Format(_T("%d"), user.GetID());
	m_editID.SetWindowText(str);
	m_editName.SetWindowText(user.GetName());
	m_editIDNo.SetWindowText(user.GetIDNo());
	m_editPhoneNo.SetWindowText(user.GetPhoneNo());
	m_editAddr.SetWindowText(user.GetAddr());
	str.Format(_T("%d"), user.GetLicense());
	m_editLicense.SetWindowText(str);
	//大修改m_editUnitName.SetWindowText(user.GetUnitName());
	str.Format(_T("%.02f"), (float)m_nDeposit / (float)g_nINT100);
	m_editDeposit.SetWindowText(str);
}