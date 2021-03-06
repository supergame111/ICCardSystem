// CUserPrestoreStatistics.cpp: 实现文件
//

#include "stdafx.h"
#include "ICCardSystem.h"
#include "CUserPrestoreStatistics.h"
#include "afxdialogex.h"


// CUserPrestoreStatistics 对话框

IMPLEMENT_DYNAMIC(CUserPrestoreStatistics, CDialogEx)

CUserPrestoreStatistics::CUserPrestoreStatistics(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USERPRESTORESTATISTICS, pParent)
	, m_bIsInitFinish(false)
	, m_strTtitle(_T("会员卡销售月度汇总表"))
	, m_strSubTtitle(_T(""))
{

}

CUserPrestoreStatistics::~CUserPrestoreStatistics()
{
}

void CUserPrestoreStatistics::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USER, m_listctrlUser);
	DDX_Control(pDX, IDC_EDIT_YEAR, m_editYear);
}


BEGIN_MESSAGE_MAP(CUserPrestoreStatistics, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_STATISTICS, &CUserPrestoreStatistics::OnBnClickedButtonStatistics)
	ON_BN_CLICKED(IDC_BUTTON_PRINT, &CUserPrestoreStatistics::OnBnClickedButtonPrint)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CUserPrestoreStatistics::OnBnClickedButtonExport)
	ON_WM_DESTROY()
	ON_MESSAGE(WM_MSGRECVPRO, &CUserPrestoreStatistics::OnMsgrecvpro)
END_MESSAGE_MAP()


// CUserPrestoreStatistics 消息处理程序


BOOL CUserPrestoreStatistics::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	InitUI();
	CTime time = CTime::GetCurrentTime();
	m_editYear.SetWindowText(time.Format(_T("%Y")));
	m_bIsInitFinish = true;
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CUserPrestoreStatistics::OnBnClickedButtonStatistics()
{
	// TODO: 在此添加控件通知处理程序代码
	m_vec2_strDataExport.clear();
	CString sz_strHead[] = { _T("客户名称"), _T("客户地址"), _T("客户状态"), _T("联系电话"),_T("一月"),_T("二月"), _T("三月"), _T("四月"), _T("五月"), _T("六月"), _T("七月"), _T("八月"), _T("九月"), _T("十月"), _T("十一月"), _T("十二月"), _T("合计") };
	m_vec2_strDataExport.resize(1);
	for (int i = 0; i < 17; ++i)
		m_vec2_strDataExport[0].push_back(sz_strHead[i]);
	std::vector<CUser> vec_user;
	GetUser(vec_user);
	int nSize = vec_user.size();
	for (int i = 0; i < nSize; ++i)
	{
		GetData(vec_user[i]);
	}
	UpdateList(m_vec2_strDataExport);
}


void CUserPrestoreStatistics::OnBnClickedButtonPrint()
{
	// TODO: 在此添加控件通知处理程序代码
	if (g_sz_p_wnd[WND_MAINVIEW])
	{
		g_sz_p_wnd[WND_MAINVIEW]->PostMessage(WM_MSGRECVPRO, (WPARAM)&m_strTtitle, MSGUSER_SETTITLE);
		g_sz_p_wnd[WND_MAINVIEW]->PostMessage(WM_MSGRECVPRO, (WPARAM)&m_strSubTtitle, MSGUSER_SETSUBTITLE);
		g_sz_p_wnd[WND_MAINVIEW]->PostMessage(WM_MSGRECVPRO, (WPARAM)&m_vec2_strDataExport, MSGUSER_PRINTUSERPRESTORE);
	}
}


void CUserPrestoreStatistics::OnBnClickedButtonExport()
{
	// TODO: 在此添加控件通知处理程序代码
	CString szFilter;
	szFilter = _T("Excel文件(*.xlsx)|*.xlsx|Excel文件(*.xls)|*.xls|所有文件(*.*)|*.*||");
	CFileDialog fileDlg(FALSE, _T("xlsx"), m_strTtitle + _T("_") + m_strSubTtitle, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (IDOK == fileDlg.DoModal())
	{
		m_strDestPath = fileDlg.GetPathName();
		m_strDemoPath = ZUtil::GetExeCatalogPath() + _T("\\DemoPrestore.xlsx");
		ZExcelExport excleexport(this);
		if (excleexport.Start())
		{
			GetDlgItem(IDC_BUTTON_EXPORT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_STATISTICS)->EnableWindow(FALSE);
		}
		else
			AfxMessageBox(_T("导出失败!"));
	}
}


void CUserPrestoreStatistics::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (m_bIsInitFinish&&nType != SIZE_MINIMIZED)
	{
		CRect rc;
		GetClientRect(&rc);
		const int nMax = 40;
		m_listctrlUser.SetRedraw(FALSE);
		m_listctrlUser.SetColumnWidth(0, rc.Width() * 3 / nMax);
		m_listctrlUser.SetColumnWidth(1, rc.Width() * 4 / nMax);
		m_listctrlUser.SetColumnWidth(2, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(3, rc.Width() * 4 / nMax);
		m_listctrlUser.SetColumnWidth(4, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(5, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(6, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(7, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(8, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(9, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(10, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(11, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(12, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(13, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(14, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(15, rc.Width() * 2 / nMax);
		m_listctrlUser.SetColumnWidth(16, rc.Width() * 2 / nMax);
		m_listctrlUser.SetRedraw(TRUE);
	}
}


void CUserPrestoreStatistics::InitUI()
{
	// TODO: 在此处添加实现代码.
	CString sz_strHead[] = { _T("客户名称"), _T("客户地址"), _T("客户状态"), _T("联系电话"),_T("一月"),_T("二月"), _T("三月"), _T("四月"), _T("五月"), _T("六月"), _T("七月"), _T("八月"), _T("九月"), _T("十月"), _T("十一月"), _T("十二月"), _T("合计") };
	const int nMax = 40;
	CRect rc;
	m_listctrlUser.GetClientRect(&rc);
	m_listctrlUser.SetExtendedStyle(m_listctrlUser.GetExtendedStyle() | LVS_EX_DOUBLEBUFFER | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listctrlUser.InsertColumn(0, sz_strHead[0], LVCFMT_LEFT, rc.Width() * 3 / nMax, 0);
	m_listctrlUser.InsertColumn(1, sz_strHead[1], LVCFMT_LEFT, rc.Width() * 4 / nMax, 1);
	m_listctrlUser.InsertColumn(2, sz_strHead[2], LVCFMT_LEFT, rc.Width() * 2 / nMax, 2);
	m_listctrlUser.InsertColumn(3, sz_strHead[3], LVCFMT_LEFT, rc.Width() * 4 / nMax, 3);
	m_listctrlUser.InsertColumn(4, sz_strHead[4], LVCFMT_LEFT, rc.Width() * 2 / nMax, 4);
	m_listctrlUser.InsertColumn(5, sz_strHead[5], LVCFMT_LEFT, rc.Width() * 2 / nMax, 5);
	m_listctrlUser.InsertColumn(6, sz_strHead[6], LVCFMT_LEFT, rc.Width() * 2 / nMax, 6);
	m_listctrlUser.InsertColumn(7, sz_strHead[7], LVCFMT_LEFT, rc.Width() * 2 / nMax, 7);
	m_listctrlUser.InsertColumn(8, sz_strHead[8], LVCFMT_LEFT, rc.Width() * 2 / nMax, 8);
	m_listctrlUser.InsertColumn(9, sz_strHead[9], LVCFMT_LEFT, rc.Width() * 2 / nMax, 9);
	m_listctrlUser.InsertColumn(10, sz_strHead[10], LVCFMT_LEFT, rc.Width() * 2 / nMax, 10);
	m_listctrlUser.InsertColumn(11, sz_strHead[11], LVCFMT_LEFT, rc.Width() * 2 / nMax, 11);
	m_listctrlUser.InsertColumn(12, sz_strHead[12], LVCFMT_LEFT, rc.Width() * 2 / nMax, 12);
	m_listctrlUser.InsertColumn(13, sz_strHead[13], LVCFMT_LEFT, rc.Width() * 2 / nMax, 13);
	m_listctrlUser.InsertColumn(14, sz_strHead[14], LVCFMT_LEFT, rc.Width() * 2 / nMax, 14);
	m_listctrlUser.InsertColumn(15, sz_strHead[15], LVCFMT_LEFT, rc.Width() * 2 / nMax, 15);
	m_listctrlUser.InsertColumn(16, sz_strHead[16], LVCFMT_LEFT, rc.Width() * 2 / nMax, 16);
}


void CUserPrestoreStatistics::GetUser(std::vector<CUser> & vec_user)
{
	CString strSql;
	CUserDB udb;
	strSql.Format(_T("SELECT * FROM User"));
	udb.Select(strSql, vec_user);
}


void CUserPrestoreStatistics::GetData(const CUser & user)
{
	CString strSql, str,strYear, strTimeStart, strTimeEnd;
	std::vector<CString> vec_str;
	m_editYear.GetWindowText(strYear);
	if (_ttoi(strYear) < 1970)
		return;
	m_strSubTtitle.Format(_T("统计年份：%s"), strYear);
	CTime time(_ttoi(strYear), 1, 1, 0, 0, 0);
	CPrestoreRecordDB prdb;
	std::vector<CRecord> vec_record;
	int nYearAmount = 0;
	vec_str.push_back(user.GetName());
	vec_str.push_back(user.GetAddr());
	CString sz_strState[] = { _T("0-未开卡"),_T("1-已开卡"), _T("2-已退卡") };
	str = sz_strState[user.GetState()];
	vec_str.push_back(str);
	vec_str.push_back(user.GetPhoneNo());
	for (int i = 0; i < 12; ++i)
	{
		CTime timeStart(time.GetYear(), i+1, 1, 0, 0, 0);
		CTime timeEnd;
		if (i == 11)
			timeEnd = CTime(time.GetYear(), 12, 31, 23, 59, 59);
		else
			timeEnd = CTime(time.GetYear(), i + 2, 1, 0, 0, 0);
		strTimeStart = timeStart.Format(_T("%Y-%m-%d %H:%M:%S"));
		strTimeEnd = timeEnd.Format(_T("%Y-%m-%d %H:%M:%S"));
		strSql.Format(_T("SELECT * FROM PrestoreRecord WHERE UserID=%d AND Time>='%s' AND Time<'%s'"), user.GetID(), strTimeStart, strTimeEnd);
		prdb.Select(strSql, vec_record);
		int nSize = vec_record.size();
		int nMonthAmount = 0;
		for (int j = 0; j < nSize; ++j)
		{
			nMonthAmount += vec_record[j].GetAmount();
		}
		str.Format(_T("%.02f"), (float)nMonthAmount / (float)g_nINT100);
		vec_str.push_back(str);
		nYearAmount += nMonthAmount;
	}
	str.Format(_T("%.02f"), (float)nYearAmount / (float)g_nINT100);
	vec_str.push_back(str);
	m_vec2_strDataExport.push_back(vec_str);
}


void CUserPrestoreStatistics::UpdateList(std::vector<std::vector<CString>> & vec2_strData)
{
	m_listctrlUser.DeleteAllItems();
	int nRow = vec2_strData.size();
	if (nRow)
	{
		int nColumn = vec2_strData[0].size();
		if (nColumn == 17)
		{
			for (int i = 1; i < nRow; ++i)
			{
				m_listctrlUser.InsertItem(i-1, vec2_strData[i][0]);
				for (int j = 1; j < nColumn; ++j)
					m_listctrlUser.SetItemText(i-1, j, vec2_strData[i][j]);
			}
		}
	}
}


void CUserPrestoreStatistics::OnExportProgressUpdate(int nProgress)
{
	if (g_sz_p_wnd[WND_MAINFRAME])
	{
		g_sz_p_wnd[WND_MAINFRAME]->PostMessage(WM_MSGRECVPRO, (WPARAM)nProgress, MSGUSER_UPDATEPROGRESS);
	}
}


void CUserPrestoreStatistics::OnExportResult(bool bResult)
{
	PostMessage(WM_MSGRECVPRO, (WPARAM)bResult, MSGUSER_EXPORTRESULT);
}


void CUserPrestoreStatistics::OnDestroy()
{
	__super::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	StopRunExport();
}


afx_msg LRESULT CUserPrestoreStatistics::OnMsgrecvpro(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case MSGUSER_EXPORTRESULT:
	{
		GetDlgItem(IDC_BUTTON_EXPORT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_STATISTICS)->EnableWindow(TRUE);
		if (wParam)
			AfxMessageBox(_T("导出成功!"));
		else
			AfxMessageBox(_T("导出失败!"));
	}
	break;
	}
	return 0;
}
