// CUserPrestore.cpp: 实现文件
//

#include "stdafx.h"
#include "ICCardSystem.h"
#include "CUserPrestore.h"
#include "afxdialogex.h"


// CUserPrestore 对话框

IMPLEMENT_DYNAMIC(CUserPrestore, CDialogEx)

CUserPrestore::CUserPrestore(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USERPRESTORE, pParent)
	, m_nDeposit(0)
{

}

CUserPrestore::~CUserPrestore()
{
}

void CUserPrestore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ID, m_editID);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_IDNO, m_editIDNo);
	DDX_Control(pDX, IDC_EDIT_PHONENO, m_editPhoneNo);
	DDX_Control(pDX, IDC_EDIT_ADDR, m_editAddr);
	DDX_Control(pDX, IDC_EDIT_LICENSE, m_editLicense);
	DDX_Control(pDX, IDC_EDIT_UNITNAME, m_editUnitName);
	DDX_Control(pDX, IDC_EDIT_BALANCE, m_editBalance);
	DDX_Control(pDX, IDC_EDIT_CARDNO, m_editCardNo);
	DDX_Control(pDX, IDC_EDIT_AMOUNT, m_editAmount);
	DDX_Control(pDX, IDC_EDIT_BALANCENEW, m_editBalanceNew);
	DDX_Control(pDX, IDC_EDIT_LASTAMOUNT, m_editLastAmount);
	DDX_Control(pDX, IDC_EDIT_TOTALAMOUNT, m_editTotalAmount);
	DDX_Control(pDX, IDC_EDIT_PRESTORETIMES, m_editPrestoreTimes);
	DDX_Control(pDX, IDC_EDIT_NOTEINFO, m_editNoteInfo);
}


BEGIN_MESSAGE_MAP(CUserPrestore, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_READCARD, &CUserPrestore::OnBnClickedButtonReadcard)
	ON_BN_CLICKED(IDC_BUTTON_PRESTORE, &CUserPrestore::OnBnClickedButtonPrestore)
	ON_EN_CHANGE(IDC_EDIT_AMOUNT, &CUserPrestore::OnEnChangeEditAmount)
	ON_MESSAGE(WM_MSGRECVPRO, &CUserPrestore::OnMsgrecvpro)
END_MESSAGE_MAP()


// CUserPrestore 消息处理程序


BOOL CUserPrestore::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	g_sz_p_wnd[WND_USERPRESTORE] = this;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CUserPrestore::OnBnClickedButtonReadcard()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strCard, strError;
	if (CCardOperator::ReadCard(strCard, strError,true))
	{
		int nCardNo, nLicense, nCardType, nUserID, nBalance;
		CCardOperator::DecodeUserCard(strCard, nCardNo, nLicense, nCardType, nUserID, nBalance);
		if (nCardNo>0&&nCardType == CCardOperator::TYPE_USER)
		{
			CString strSql, strBalance, strLastAmount(_T("0")), strTotalAmount, strPrestoreTimes(_T("0"));
			std::vector<CUser> vec_user;
			strSql.Format(_T("SELECT * FROM User WHERE ID=%d ORDER BY ID"), nUserID);
			m_udb.Select(strSql, vec_user);
			if (vec_user.size() == 1)
			{
				vec_user[0].SetCardNo(nCardNo);
				vec_user[0].SetLicense(nLicense);
				m_udb.UpdateModifyInfo(vec_user[0]);
				InsertEdit(vec_user[0]);
				m_SelectUser = vec_user[0];
				strBalance.Format(_T("%.02f"), (float)nBalance / (float)g_nINT100);
				m_editBalance.SetWindowText(strBalance);
				strTotalAmount.Format(_T("%d"), vec_user[0].GetTotalAmount()/ g_nINT100);
				m_editTotalAmount.SetWindowText(strTotalAmount);
				std::vector<CRecord> vec_record;
				strSql.Format(_T("SELECT * FROM PrestoreRecord WHERE UserID=%d ORDER BY Time DESC"), nUserID);
				m_prdb.Select(strSql, vec_record);
				if (vec_record.size())
				{
					strLastAmount.Format(_T("%d"), vec_record[0].GetAmount()/ g_nINT100);
					strPrestoreTimes.Format(_T("%d"), vec_record.size());
				}
				m_editLastAmount.SetWindowText(strLastAmount);
				m_editPrestoreTimes.SetWindowText(strPrestoreTimes);
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


void CUserPrestore::OnBnClickedButtonPrestore()
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
		AfxMessageBox(_T("预存金额不能为0!"));
		return;
	}
	CString strCard, strError;
	if (CCardOperator::ReadCard(strCard, strError))
	{
		int nCardNo, nLicense, nCardType, nUserID, nBalance;
		CCardOperator::DecodeUserCard(strCard, nCardNo, nLicense, nCardType, nUserID, nBalance);
		if (nCardNo > 0 && nCardType == CCardOperator::TYPE_USER&&nUserID == nID)
		{
			strCard = CCardOperator::EncodeUserCard(m_SelectUser.GetCardNo(), m_SelectUser.GetLicense(), CCardOperator::TYPE_USER, m_SelectUser.GetID(), nBalance + nAmount);
			if (CCardOperator::WriteCard(strCard, strError))
			{
				int nIDRecord;
				std::vector<CRecord> vec_record;
				m_prdb.Select(_T("SELECT * FROM PrestoreRecord ORDER BY ID DESC LIMIT 1"), vec_record);
				if (vec_record.size() == 1)
					nIDRecord = vec_record[0].GetID() + 1;
				else
					nIDRecord = 1;
				GetDeposit(m_SelectUser);
				CRecord record(nIDRecord, m_SelectUser.GetID(), nBalance, nAmount, nBalance + nAmount, m_nDeposit,0, strNoteInfo, g_employee.GetID(), _T(""));
				if (m_prdb.Insert(record))
				{
					m_SelectUser.SetTotalAmount(m_SelectUser.GetTotalAmount()+ nAmount);
					m_udb.UpdateTotalAmount(m_SelectUser);
					OnBnClickedButtonReadcard();
					AfxMessageBox(_T("预存成功!"));
				}
				else
					AfxMessageBox(_T("预存失败!"));
			}
			else
				AfxMessageBox(_T("预存失败!\r\n") + strError);
		}
		else
			AfxMessageBox(_T("请重新读卡!"));
	}
	else
		AfxMessageBox(_T("预存失败!\r\n") + strError);
}


void CUserPrestore::OnEnChangeEditAmount()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CString strBalance,strAmount;
	float fBalance,fAmount;
	m_editBalance.GetWindowText(strBalance);
	m_editAmount.GetWindowText(strAmount);
	fBalance = (float)_ttof(strBalance);
	fAmount = (float)_ttof(strAmount);
	if (fAmount > 999999.0f)
	{
		fAmount = 999999.0f;
		strAmount.Format(_T("%d"), 999999);
		m_editAmount.SetWindowText(strAmount);
		m_editAmount.SetSel(strAmount.GetLength(), strAmount.GetLength());
	}
	fBalance += fAmount;
	strBalance.Format(_T("%.2f"), fBalance);
	m_editBalanceNew.SetWindowText(strBalance);
}


void CUserPrestore::GetDeposit(const CUser & user)
{
	CString strSql;
	std::vector<CRecord> vec_record;
	strSql.Format(_T("SELECT * FROM ReturnDepositRecord WHERE UserID=%d ORDER BY Time DESC LIMIT 1"), user.GetID());
	m_rdrdb.Select(strSql, vec_record);
	if (vec_record.size() == 1)
		m_nDeposit = vec_record[0].GetAmountNew();
	else
		m_nDeposit = user.GetDeposit();
}


void CUserPrestore::InsertEdit(const CUser & user)
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
	m_editUnitName.SetWindowText(user.GetUnitName());
	str.Format(_T("%d"), user.GetCardNo());
	m_editCardNo.SetWindowText(str);
}

afx_msg LRESULT CUserPrestore::OnMsgrecvpro(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case MSGUSER_SHOWPRESTORE:
	{
		ShowWindow(SW_SHOW);
	}
	break;
	}
	return 0;
}
