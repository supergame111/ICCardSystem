// CUserReopenCard.cpp: 实现文件
//

#include "stdafx.h"
#include "ICCardSystem.h"
#include "CUserReopenCard.h"
#include "afxdialogex.h"


// CUserReopenCard 对话框

IMPLEMENT_DYNAMIC(CUserReopenCard, CDialogEx)

CUserReopenCard::CUserReopenCard(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USERREOPENCARD, pParent)
	, m_nDeposit(0)
{

}

CUserReopenCard::~CUserReopenCard()
{
}

void CUserReopenCard::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CONDITION, m_comboCondition);
	DDX_Control(pDX, IDC_LIST_USER, m_listctrlUser);
	DDX_Control(pDX, IDC_EDIT_KEYWORD, m_editKeyword);
	DDX_Control(pDX, IDC_EDIT_ID, m_editID);
	DDX_Control(pDX, IDC_EDIT_NAME, m_editName);
	DDX_Control(pDX, IDC_EDIT_IDNO, m_editIDNo);
	DDX_Control(pDX, IDC_EDIT_PHONENO, m_editPhoneNo);
	DDX_Control(pDX, IDC_EDIT_ADDR, m_editAddr);
	DDX_Control(pDX, IDC_EDIT_LICENSE, m_editLicense);
	DDX_Control(pDX, IDC_EDIT_UNITNAME, m_editUnitName);
	DDX_Control(pDX, IDC_EDIT_LASTAMOUNT, m_editLastAmount);
	DDX_Control(pDX, IDC_EDIT_TOTALAMOUNT, m_editTotalAmount);
	DDX_Control(pDX, IDC_EDIT_PRESTORETIMES, m_editPrestoreTimes);
	DDX_Control(pDX, IDC_EDIT_AMOUNT, m_editAmount);
	DDX_Control(pDX, IDC_EDIT_CARDNO, m_editCardNo);
	DDX_Control(pDX, IDC_EDIT_NOTEINFO, m_editNoteInfo);
}


BEGIN_MESSAGE_MAP(CUserReopenCard, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CUserReopenCard::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_REOPENCARD, &CUserReopenCard::OnBnClickedButtonReopencard)
	ON_BN_CLICKED(IDC_BUTTON_PRESTORE, &CUserReopenCard::OnBnClickedButtonPrestore)
	ON_NOTIFY(NM_CLICK, IDC_LIST_USER, &CUserReopenCard::OnNMClickListUser)
END_MESSAGE_MAP()


// CUserReopenCard 消息处理程序


BOOL CUserReopenCard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUI();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CUserReopenCard::OnBnClickedButtonSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strKeyword, strSql;
	m_editKeyword.GetWindowText(strKeyword);
	std::vector<CUser> vec_user;
	if (strKeyword.IsEmpty())
		strSql.Format(_T("SELECT * FROM User ORDER BY ID"));
	else
	{
		switch (m_comboCondition.GetCurSel())
		{
		case 0:strSql.Format(_T("SELECT * FROM User WHERE ID=%d ORDER BY ID"), _ttoi(strKeyword)); break;
		case 1:strSql.Format(_T("SELECT * FROM User WHERE Name LIKE '%%%s%%'ORDER BY ID"), strKeyword); break;
		case 2:strSql.Format(_T("SELECT * FROM User WHERE PhoneNo LIKE '%%%s%%'ORDER BY ID"), strKeyword); break;
		case 3:strSql.Format(_T("SELECT * FROM User WHERE Addr LIKE '%%%s%%'ORDER BY ID"), strKeyword); break;
		case 4:strSql.Format(_T("SELECT * FROM User WHERE License=%d ORDER BY ID"), _ttoi(strKeyword)); break;
		}
	}
	if (m_comboCondition.GetCurSel() != -1)
	{
		m_udb.Select(strSql, vec_user);
		UpdateList(vec_user);
	}
}


void CUserReopenCard::OnBnClickedButtonReopencard()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strAmount, strNoteInfo;
	m_editAmount.GetWindowText(strAmount);
	m_editNoteInfo.GetWindowText(strNoteInfo);
	int nAmount = _ttoi(strAmount)*g_nINT100;
	if (nAmount == 0)
	{
		AfxMessageBox(_T("补卡费用不能为0!"));
		return;
	}
	CString strCard, strError;
	strCard = CCardOperator::EncodeUserCard(m_SelectUser.GetCardNo(), m_SelectUser.GetLicense(), CCardOperator::TYPE_USER, m_SelectUser.GetID(), 0x00);
	if (CCardOperator::WriteCard(strCard, strError,true))
	{
		int nID;
		std::vector<CRecord> vec_record;
		m_prdb.Select(_T("SELECT * FROM ReopenCardRecord ORDER BY ID DESC LIMIT 1"), vec_record);
		if (vec_record.size() == 1)
			nID = vec_record[0].GetID() + 1;
		else
			nID = 1;
		GetDeposit(m_SelectUser);
		CRecord record(nID, m_SelectUser.GetID(), 0, 0, 0, m_nDeposit,nAmount, strNoteInfo, g_employee.GetID(), _T(""));
		if (m_rcrdb.Insert(record))
		{
			GetDlgItem(IDC_BUTTON_REOPENCARD)->EnableWindow(FALSE);
			m_editAmount.SetWindowText(_T(""));
			OnBnClickedButtonSearch();
			AfxMessageBox(_T("补卡成功!"));
			return;
		}
		else
			CCardOperator::ClearUserCard();
	}
	OnBnClickedButtonSearch();
	AfxMessageBox(_T("补卡失败!\r\n") + strError);
}


void CUserReopenCard::OnBnClickedButtonPrestore()
{
	// TODO: 在此添加控件通知处理程序代码
	if (g_sz_p_wnd[WND_USERPRESTORE])
		g_sz_p_wnd[WND_USERPRESTORE]->PostMessage(WM_MSGRECVPRO, 0, MSGUSER_SHOWPRESTORE);
}


void CUserReopenCard::OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int & nItem = pNMItemActivate->iItem;
	if (nItem != -1)
	{
		int nID = _ttoi(m_listctrlUser.GetItemText(nItem, 0));
		InsertEditByID(nID);
	}
}


void CUserReopenCard::InitUI()
{
	// TODO: 在此处添加实现代码.
	CString sz_strCondition[] = { _T("客户编号"),_T("客户名称"), _T("客户手机号"), _T("客户地址"), _T("授权码") };
	for (int i = 0; i < sizeof(sz_strCondition) / sizeof(CString); ++i)
		m_comboCondition.AddString(sz_strCondition[i]);
	m_comboCondition.SetCurSel(0);
	const int nMax = 13;
	CRect rc;
	m_listctrlUser.GetClientRect(&rc);
	m_listctrlUser.SetExtendedStyle(m_listctrlUser.GetExtendedStyle() | LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listctrlUser.InsertColumn(0, _T("客户编号"), LVCFMT_LEFT, rc.Width() * 2 / nMax, 0);
	m_listctrlUser.InsertColumn(1, _T("客户名称"), LVCFMT_LEFT, rc.Width() * 2 / nMax, 1);
	m_listctrlUser.InsertColumn(2, _T("手机"), LVCFMT_LEFT, rc.Width() * 3 / nMax, 2);
	m_listctrlUser.InsertColumn(3, _T("地址"), LVCFMT_LEFT, rc.Width() * 3 / nMax, 3);
	m_listctrlUser.InsertColumn(4, _T("状态"), LVCFMT_LEFT, rc.Width() * 2 / nMax, 4);
	GetDlgItem(IDC_BUTTON_REOPENCARD)->EnableWindow(FALSE);
}


void CUserReopenCard::UpdateList(const std::vector<CUser> & vec_user)
{
	m_listctrlUser.DeleteAllItems();
	int nSize = vec_user.size();
	for (int i = 0; i < nSize; ++i)
	{
		CString strID, strState;
		strID.Format(_T("%d"), vec_user[i].GetID());
		CString sz_strState[] = { _T("0-未开卡"),_T("1-已开卡"), _T("2-已退卡") };
		if (vec_user[i].GetState() < CUser::STATE_ERROR)
			strState = sz_strState[vec_user[i].GetState()];
		else
			strState = sz_strState[0];
		m_listctrlUser.InsertItem(i, strID);
		m_listctrlUser.SetItemText(i, 1, vec_user[i].GetName());
		m_listctrlUser.SetItemText(i, 2, vec_user[i].GetPhoneNo());
		m_listctrlUser.SetItemText(i, 3, vec_user[i].GetAddr());
		m_listctrlUser.SetItemText(i, 4, strState);
	}
}


void CUserReopenCard::GetDeposit(const CUser & user)
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


void CUserReopenCard::InsertEdit(const CUser & user)
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
	if (user.GetCardNo())
		str.Format(_T("%d"), user.GetCardNo());
	else
		str.Empty();
	m_editCardNo.SetWindowText(str);
	str.Format(_T("%d"), user.GetTotalAmount() / g_nINT100);
	m_editTotalAmount.SetWindowText(str);
	CString strSql, strLastAmount(_T("0")), strPrestoreTimes(_T("0"));
	std::vector<CRecord> vec_record;
	strSql.Format(_T("SELECT * FROM PrestoreRecord WHERE UserID=%d ORDER BY Time DESC"), user.GetID());
	m_prdb.Select(strSql, vec_record);
	if (vec_record.size())
	{
		strLastAmount.Format(_T("%d"), vec_record[0].GetAmount() / g_nINT100);
		strPrestoreTimes.Format(_T("%d"), vec_record.size());
	}
	m_editLastAmount.SetWindowText(strLastAmount);
	m_editPrestoreTimes.SetWindowText(strPrestoreTimes);
}

void CUserReopenCard::InsertEditByID(int nID)
{
	std::vector<CUser> vec_user;
	CString strSql;
	strSql.Format(_T("SELECT * FROM User WHERE ID=%d ORDER BY ID"), nID);
	m_udb.Select(strSql, vec_user);
	if (vec_user.size() == 1)
	{
		InsertEdit(vec_user[0]);
		m_SelectUser = vec_user[0];
		if (vec_user[0].GetState() == CUser::STATE_OPEN)
			GetDlgItem(IDC_BUTTON_REOPENCARD)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_BUTTON_REOPENCARD)->EnableWindow(FALSE);
	}
}