// CUserOpenCard.cpp: 实现文件
//

#include "stdafx.h"
#include "ICCardSystem.h"
#include "CUserOpenCard.h"
#include "afxdialogex.h"


// CUserOpenCard 对话框
const int nTimerAuto = 0;

IMPLEMENT_DYNAMIC(CUserOpenCard, CDialogEx)

CUserOpenCard::CUserOpenCard(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USEROPENCARD, pParent)
	, m_nCardType(CCardOperator::TYPE_USER_RECHARGE)
	, m_nCardCount(0)
{

}

CUserOpenCard::~CUserOpenCard()
{
}

void CUserOpenCard::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_EDIT_STATE, m_editState);
	DDX_Control(pDX, IDC_EDIT_CARDNO, m_editCardNo);
	DDX_Control(pDX, IDC_EDIT_DEPOSIT, m_editDeposit);
	DDX_Control(pDX, IDC_EDIT_AMOUNT, m_editAmount);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DEADLINE, m_datetimeDeadline);
	DDX_Control(pDX, IDC_CHECK_AUTO, m_checkAuto);
	DDX_Control(pDX, IDC_STATIC_CARDCOUNT, m_staticCardCount);
}


BEGIN_MESSAGE_MAP(CUserOpenCard, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CUserOpenCard::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_READLICENSECARD, &CUserOpenCard::OnBnClickedButtonReadlicensecard)
	ON_BN_CLICKED(IDC_BUTTON_OPENCARD, &CUserOpenCard::OnBnClickedButtonOpencard)
	ON_NOTIFY(NM_CLICK, IDC_LIST_USER, &CUserOpenCard::OnNMClickListUser)
	ON_BN_CLICKED(IDC_RADIO_TIME, &CUserOpenCard::OnBnClickedRadioTime)
	ON_BN_CLICKED(IDC_RADIO_RECHARGE, &CUserOpenCard::OnBnClickedRadioRecharge)
	ON_BN_CLICKED(IDC_CHECK_AUTO, &CUserOpenCard::OnBnClickedCheckAuto)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CUserOpenCard 消息处理程序


BOOL CUserOpenCard::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUI();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CUserOpenCard::OnBnClickedButtonSearch()
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


void CUserOpenCard::OnBnClickedButtonReadlicensecard()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strCard, strError;
	if (CCardOperator::ReadCard(strCard, strError, true))
	{
		int nLicenseCard, nCardType;
		CString strCardNo;
		CCardOperator::DecodeCard(strCard, strCardNo, nLicenseCard, nCardType);
		if (nCardType == CCardOperator::TYPE_LICENSE)
		{
			CCardOperator::DecodeLicenseCard(strCard, strCardNo, nLicenseCard, nCardType);
			SetDlgItemInt(IDC_EDIT_LICENSECARD, nLicenseCard);
			CString strSql;
			std::vector<CUser> vec_user;
			strSql.Format(_T("SELECT * FROM User WHERE License=%d"), nLicenseCard);
			m_udb.Select(strSql, vec_user);
			if (vec_user.size() == 1)
			{
				InsertEdit(vec_user[0]);
				m_SelectUser = vec_user[0];
			}
		}
		else
			AfxMessageBox(_T("此卡非授权卡!"));
	}
	else
		AfxMessageBox(_T("读卡失败!\r\n") + strError);
}


void CUserOpenCard::OnBnClickedButtonOpencard()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strInfo;
	OpenCard(strInfo);
	OnBnClickedButtonSearch();
	AfxMessageBox(strInfo);
}


void CUserOpenCard::OnBnClickedRadioTime()
{
	// TODO: 在此添加控件通知处理程序代码
	m_editAmount.EnableWindow(FALSE);
	m_datetimeDeadline.EnableWindow(TRUE);
	m_nCardType = CCardOperator::TYPE_USER_TIME;
}


void CUserOpenCard::OnBnClickedRadioRecharge()
{
	// TODO: 在此添加控件通知处理程序代码
	m_editAmount.EnableWindow(TRUE);
	m_datetimeDeadline.EnableWindow(FALSE);
	m_nCardType = CCardOperator::TYPE_USER_RECHARGE;
}


void CUserOpenCard::OnBnClickedCheckAuto()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_checkAuto.GetCheck())
	{
		GetDlgItem(IDC_BUTTON_READLICENSECARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OPENCARD)->EnableWindow(FALSE);
		m_listctrlUser.EnableWindow(FALSE);
		m_nCardCount = 0;
		m_staticCardCount.SetWindowText(_T("开卡数量:0"));
		SetTimer(nTimerAuto, 1000, NULL);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_READLICENSECARD)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_OPENCARD)->EnableWindow(TRUE);
		m_listctrlUser.EnableWindow(TRUE);
		KillTimer(nTimerAuto);
		OnBnClickedButtonSearch();
	}
}


void CUserOpenCard::OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult)
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


void CUserOpenCard::InitUI()
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
	m_listctrlUser.InsertColumn(4, _T("客户状态"), LVCFMT_LEFT, rc.Width() * 2 / nMax, 4);
	CheckDlgButton(IDC_RADIO_RECHARGE, TRUE);
	OnBnClickedRadioRecharge();
}


void CUserOpenCard::UpdateList(const std::vector<CUser> & vec_user)
{
	m_listctrlUser.DeleteAllItems();
	int nSize = vec_user.size();
	for (int i = 0; i < nSize; ++i)
	{
		CString strID, strState;
		strID.Format(_T("%d"), vec_user[i].GetID());
		CString sz_strState[] = { _T("0-未开卡"),_T("1-已开卡"), _T("2-已退卡") };
		strState = sz_strState[vec_user[i].GetState()];
		m_listctrlUser.InsertItem(i, strID);
		m_listctrlUser.SetItemText(i, 1, vec_user[i].GetName());
		m_listctrlUser.SetItemText(i, 2, vec_user[i].GetPhoneNo());
		m_listctrlUser.SetItemText(i, 3, vec_user[i].GetAddr());
		m_listctrlUser.SetItemText(i, 4, strState);
	}
}


void CUserOpenCard::InsertEdit(const CUser & user)
{
	CString str;
	str.Format(_T("%d"), user.GetID());
	m_editID.SetWindowText(str);
	m_editName.SetWindowText(user.GetName());
	m_editIDNo.SetWindowText(user.GetIDNo());
	m_editPhoneNo.SetWindowText(user.GetPhoneNo());
	m_editAddr.SetWindowText(user.GetAddr());
	if (user.GetLicense())
		str.Format(_T("%d"), user.GetLicense());
	else
		str.Empty();
	m_editLicense.SetWindowText(str);
	CString sz_strState[] = { _T("0-未开卡"),_T("1-已开卡"), _T("2-已退卡") };
	str = sz_strState[user.GetState()];
	m_editState.SetWindowText(str);
}

void CUserOpenCard::InsertEditByID(int nID)
{
	std::vector<CUser> vec_user;
	CString strSql;
	strSql.Format(_T("SELECT * FROM User WHERE ID=%d ORDER BY ID"), nID);
	m_udb.Select(strSql, vec_user);
	if (vec_user.size() == 1)
	{
		InsertEdit(vec_user[0]);
		m_SelectUser = vec_user[0];
	}
}


void CUserOpenCard::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	static int nTimeoutCount = 0;
	switch (nIDEvent)
	{
	case nTimerAuto:
	{
		CString strInfo;
		int nRtn = OpenCard(strInfo);
		switch (nRtn)
		{
		case ERROR_OK:
		{
			nTimeoutCount = 0;
			++m_nCardCount;
			CString strText;
			strText.Format(_T("开卡数量:%d"), m_nCardCount);
			m_staticCardCount.SetWindowText(strText);
		}
		break;
		case ERROR_READCARD:
		{
			++nTimeoutCount;
			if (nTimeoutCount >= 60)
			{
				nTimeoutCount = 0;
				m_checkAuto.SetCheck(FALSE);
				OnBnClickedCheckAuto();
			}
		}
		break;
		case ERROR_OTHER:
		{
			m_checkAuto.SetCheck(FALSE);
			OnBnClickedCheckAuto();
			AfxMessageBox(strInfo);
		}
		break;
		}
	}
	break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


int CUserOpenCard::OpenCard(CString & strInfo)
{
	// TODO: 在此处添加实现代码.
	CString strSql;
	int nLicense, nLicenseCard, nDeposit, nAmount;
	nLicense = GetDlgItemInt(IDC_EDIT_LICENSE);
	nLicenseCard = GetDlgItemInt(IDC_EDIT_LICENSECARD);
	if (!nLicenseCard)
	{
		strInfo =_T("请读取授权卡!");
		return ERROR_OTHER;
	}
	if (!nLicense)
	{
		std::vector<CUser> vec_user;
		strSql.Format(_T("SELECT * FROM User WHERE License=%d"), nLicenseCard);
		m_udb.Select(strSql, vec_user);
		if (vec_user.size())
		{
			strInfo = _T("此授权卡已与其他客户匹配,请更换授权卡!");
			return ERROR_OTHER;
		}
	}
	if (nLicense&&nLicense != nLicenseCard)
	{
		strInfo =_T("此授权卡非该客户所有!");
		return ERROR_OTHER;
	}
	nLicense = nLicenseCard;
	CString strCard, strCardNo, strError, strDeadline;
	if (CCardOperator::ReadCardNo(strCardNo, strError))
	{
		SetDlgItemInt(IDC_EDIT_LICENSE, nLicense);
		m_editCardNo.SetWindowText(strCardNo);
	}
	else
	{
		strInfo =_T("开卡失败!\r\n") + strError;
		return ERROR_READCARD;
	}
	nDeposit = GetDlgItemInt(IDC_EDIT_DEPOSIT)*g_nINT100;
	if (m_nCardType == CCardOperator::TYPE_USER_RECHARGE)
	{
		nAmount = GetDlgItemInt(IDC_EDIT_AMOUNT)*g_nINT100;
	}
	else
	{
		CTime timeDeadline;
		m_datetimeDeadline.GetTime(timeDeadline);
		strDeadline = timeDeadline.Format(_T("%Y%m%d"));
		nAmount = _tcstol(strDeadline, NULL, 16);
	}
	std::vector<CCard> vec_card;
	strSql.Format(_T("SELECT * FROM Card WHERE No='%s' AND State=%d"),  strCardNo,CCard::STATE_OPEN);
	m_cdb.Select(strSql, vec_card);
	if (vec_card.size() == 1)
	{
		strInfo = _T("此卡已开过，请退卡了重开!");
		return ERROR_READCARD;
	}
	strCard = CCardOperator::EncodeUserCard(strCardNo, nLicense, m_nCardType, m_SelectUser.GetID(), nAmount);
	if (m_SelectUser.GetID() && CCardOperator::WriteCard(strCard, strError, true))
	{
		m_SelectUser.SetLicense(nLicense);
		m_SelectUser.SetState(CUser::STATE_OPEN);
		if (m_udb.UpdateOpenCard(m_SelectUser))
		{
			bool bCardSuccess = false;
			strSql.Format(_T("SELECT * FROM Card WHERE UserID=%d AND No='%s'"), m_SelectUser.GetID(), strCardNo);
			m_cdb.Select(strSql, vec_card);
			if (vec_card.size() == 1)
			{
				m_SelectCard = CCard(vec_card[0].GetID(), vec_card[0].GetUserID(), vec_card[0].GetNo(), m_nCardType, strDeadline, nDeposit, vec_card[0].GetTotalAmount(),CCard::STATE_OPEN, g_employee.GetID(), _T(""), g_employee.GetID(), _T(""));
				bCardSuccess=m_cdb.UpdateOpenCard(m_SelectCard);
			}
			else
			{
				int nIDCard;
				m_cdb.Select(_T("SELECT * FROM Card ORDER BY ID DESC LIMIT 1"), vec_card);
				if (vec_card.size() == 1)
					nIDCard = vec_card[0].GetID() + 1;
				else
					nIDCard = 1;
				m_SelectCard = CCard(nIDCard, m_SelectUser.GetID(), strCardNo, m_nCardType, strDeadline, nDeposit,0, CCard::STATE_OPEN, g_employee.GetID(), _T(""), g_employee.GetID(), _T(""));
				bCardSuccess=m_cdb.Insert(m_SelectCard);
			}
			if (bCardSuccess)
			{
				int nIDRecord;
				std::vector<CRecord> vec_record;
				m_idrdb.Select(_T("SELECT * FROM InitDepositRecord ORDER BY ID DESC LIMIT 1"), vec_record);
				if (vec_record.size() == 1)
					nIDRecord = vec_record[0].GetID() + 1;
				else
					nIDRecord = 1;
				CRecord recordDeposit(nIDRecord, m_SelectUser.GetID(), m_SelectCard.GetNo(), 0, nDeposit, nDeposit, nDeposit, _T("开卡_押金"), g_employee.GetID(), _T(""));
				m_idrdb.Insert(recordDeposit);//开卡押金
				if (m_nCardType == CCardOperator::TYPE_USER_RECHARGE)
				{
					m_prdb.Select(_T("SELECT * FROM PrestoreRecord ORDER BY ID DESC LIMIT 1"), vec_record);
					if (vec_record.size() == 1)
						nIDRecord = vec_record[0].GetID() + 1;
					else
						nIDRecord = 1;
					CRecord recordPrestore(nIDRecord, m_SelectUser.GetID(), m_SelectCard.GetNo(), 0, nAmount, nAmount, nDeposit, _T("开卡_充值"), g_employee.GetID(), _T(""));
					m_prdb.Insert(recordPrestore);//充值
					m_SelectUser.SetTotalAmount(m_SelectUser.GetTotalAmount() + nAmount);
					m_udb.UpdateTotalAmount(m_SelectUser);
					m_SelectCard.SetTotalAmount(m_SelectCard.GetTotalAmount() + nAmount);
					m_cdb.UpdateTotalAmount(m_SelectCard);
				}
				m_editState.SetWindowText(_T("1 - 已开卡"));
				strInfo = _T("开卡成功!");
				return ERROR_OK;
			}
		}
		CCardOperator::ClearUserCard();
	}
	strInfo =_T("开卡失败!\r\n") + strError;
	return ERROR_READCARD;
}
