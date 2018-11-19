// CUserInfoQuery.cpp: 实现文件
//

#include "stdafx.h"
#include "ICCardSystem.h"
#include "CUserInfoQuery.h"
#include "afxdialogex.h"


// CUserInfoQuery 对话框

IMPLEMENT_DYNAMIC(CUserInfoQuery, CDialogEx)

CUserInfoQuery::CUserInfoQuery(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USERINFOQUERY, pParent)
	, m_bIsInitFinish(false)
{

}

CUserInfoQuery::~CUserInfoQuery()
{
}

void CUserInfoQuery::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_CONDITION, m_comboCondition);
	DDX_Control(pDX, IDC_LIST_USER, m_listctrlUser);
	DDX_Control(pDX, IDC_EDIT_KEYWORD, m_editKeyword);
}


BEGIN_MESSAGE_MAP(CUserInfoQuery, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CUserInfoQuery::OnBnClickedButtonSearch)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CUserInfoQuery 消息处理程序


BOOL CUserInfoQuery::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUI();
	m_bIsInitFinish = true;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CUserInfoQuery::OnBnClickedButtonSearch()
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
		case 4:strSql.Format(_T("SELECT * FROM User WHERE UnitID=%d ORDER BY ID"), _ttoi(strKeyword)); break;
		}
	}
	if (m_comboCondition.GetCurSel() != -1)
	{
		m_udb.Select(strSql, vec_user);
		UpdateList(vec_user);
	}
}


void CUserInfoQuery::InitUI()
{
	// TODO: 在此处添加实现代码.
	CString sz_strCondition[] = { _T("客户编号"),_T("客户名称"), _T("客户手机号"), _T("客户地址"), _T("单位编号") };
	for (int i = 0; i < sizeof(sz_strCondition) / sizeof(CString); ++i)
		m_comboCondition.AddString(sz_strCondition[i]);
	m_comboCondition.SetCurSel(0);
	const int nMax = 38;
	CRect rc;
	m_listctrlUser.GetClientRect(&rc);
	m_listctrlUser.SetExtendedStyle(m_listctrlUser.GetExtendedStyle() | LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listctrlUser.InsertColumn(0, _T("客户编号"), LVCFMT_LEFT, rc.Width() * 2 / nMax, 0);
	m_listctrlUser.InsertColumn(1, _T("客户名称"), LVCFMT_LEFT, rc.Width() * 2 / nMax, 1);
	m_listctrlUser.InsertColumn(2, _T("手机"), LVCFMT_LEFT, rc.Width() * 4 / nMax, 2);
	m_listctrlUser.InsertColumn(3, _T("地址"), LVCFMT_LEFT, rc.Width() * 5 / nMax, 3);
	m_listctrlUser.InsertColumn(4, _T("状态"), LVCFMT_LEFT, rc.Width() * 2 / nMax, 4);
	m_listctrlUser.InsertColumn(5, _T("身份证"), LVCFMT_LEFT, rc.Width() * 5 / nMax, 5);
	m_listctrlUser.InsertColumn(6, _T("单位编号"), LVCFMT_LEFT, rc.Width() * 2 / nMax, 6);
	m_listctrlUser.InsertColumn(7, _T("单位名称"), LVCFMT_LEFT, rc.Width() * 2 / nMax, 7);
	m_listctrlUser.InsertColumn(8, _T("设备编号"), LVCFMT_LEFT, rc.Width() * 2 / nMax, 8);
	m_listctrlUser.InsertColumn(9, _T("累计充值"), LVCFMT_LEFT, rc.Width() * 2 / nMax, 9);
	m_listctrlUser.InsertColumn(10, _T("押金"), LVCFMT_LEFT, rc.Width() * 2 / nMax, 10);
	m_listctrlUser.InsertColumn(11, _T("开卡时间"), LVCFMT_LEFT, rc.Width() * 3 / nMax, 11);
	m_listctrlUser.InsertColumn(12, _T("备注"), LVCFMT_LEFT, rc.Width() * 4 / nMax, 12);
}


void CUserInfoQuery::UpdateList(const std::vector<CUser> & vec_user)
{
	m_listctrlUser.DeleteAllItems();
	int nSize = vec_user.size();
	for (int i = 0; i < nSize; ++i)
	{
		CString strID, strUnitID, strState,strDeviceID,strTotalAmount,strDeposit;
		strID.Format(_T("%d"), vec_user[i].GetID());
		strUnitID.Format(_T("%d"), vec_user[i].GetUnitID());
		if (vec_user[i].GetDeviceID())
			strDeviceID.Format(_T("%d"), vec_user[i].GetDeviceID());
		strTotalAmount.Format(_T("%.02f"), (float)(vec_user[i].GetTotalAmount() / (float)g_nINT100));
		strDeposit.Format(_T("%.02f"), (float)(vec_user[i].GetDeposit() / (float)g_nINT100));
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
		m_listctrlUser.SetItemText(i, 5, vec_user[i].GetIDNo());
		m_listctrlUser.SetItemText(i, 6, strUnitID);
		m_listctrlUser.SetItemText(i, 7, vec_user[i].GetUnitName());
		m_listctrlUser.SetItemText(i, 8, strDeviceID);
		m_listctrlUser.SetItemText(i, 9, strTotalAmount);
		m_listctrlUser.SetItemText(i, 10, strDeposit);
		m_listctrlUser.SetItemText(i, 11, vec_user[i].GetTimeOpenCard());
		m_listctrlUser.SetItemText(i, 12, vec_user[i].GetNoteInfo());
	}
}

void CUserInfoQuery::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_bIsInitFinish&&nType != SIZE_MINIMIZED)
	{
		CRect rc;
		GetClientRect(&rc);
		const int nMax = 38;
		m_listctrlUser.SetRedraw(FALSE);
		m_listctrlUser.SetColumnWidth(0, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(1, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(2, rc.Width() * 4 / nMax);
		m_listctrlUser.SetColumnWidth(3, rc.Width() * 5 / nMax);
		m_listctrlUser.SetColumnWidth(4, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(5, rc.Width() * 5 / nMax);
		m_listctrlUser.SetColumnWidth(6, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(7, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(8, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(9, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(10, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(11, rc.Width() * 3 / nMax);
		m_listctrlUser.SetColumnWidth(12, rc.Width() * 4 / nMax);
		m_listctrlUser.SetRedraw(TRUE);
	}
}
