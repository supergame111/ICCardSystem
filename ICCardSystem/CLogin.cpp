// CLogin.cpp: 实现文件
//

#include "stdafx.h"
#include "ICCardSystem.h"
#include "CLogin.h"
#include "afxdialogex.h"


// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LOGO, m_btnLogo);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLogin::OnBnClickedOk)
END_MESSAGE_MAP()


// CLogin 消息处理程序


BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon, FALSE);
	std::vector<CEmployee> vec_employee;
	m_edb.Select(_T("SELECT * FROM Employee WHERE ID=100"), vec_employee);
	if (vec_employee.size() != 1)
	{
		CEmployee employee(100, _T("admin"), _T("123123"), 0, 1);
		m_edb.Insert(employee);
	}
	m_btnLogo.SetBitmap(IDB_BITMAP_LOGO, IDB_BITMAP_LOGO);
	m_btnLogo.DrawBorder(FALSE);
	m_btnLogo.SetFlat(TRUE);
	m_btnLogo.EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLogin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strID, strPassword,strSql;
	GetDlgItemText(IDC_EDIT_ID, strID);
	GetDlgItemText(IDC_EDIT_PASSWORD, strPassword);
	std::vector<CEmployee> vec_employee;
	strSql.Format(_T("SELECT * FROM Employee WHERE ID=%d"),_ttoi(strID));
	m_edb.Select(strSql, vec_employee);
	if (vec_employee.size() == 1)
	{
		if(!vec_employee[0].IsUsing())
		{
			AfxMessageBox(_T("该工号已停用!"));
			return;
		}
		if (vec_employee[0].GetPassword() != strPassword)
		{
			AfxMessageBox(_T("密码错误!"));
			return;
		}
		g_employee = vec_employee[0];
	}
	else
	{
		AfxMessageBox(_T("工号不存在!"));
		return;
	}
	CDialogEx::OnOK();
}
