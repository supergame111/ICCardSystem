
// MainFrm.cpp: CMainFrame 类的实现
//

#include "stdafx.h"
#include "ICCardSystem.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, &CMainFrame::OnToolbarCreateNew)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND_RANGE(ID_INDICATOR_EMPLOYEE, ID_INDICATOR_EMPLOYEE, NULL)
	ON_COMMAND(ID_SYSTEM_EMPLOYEE, &CMainFrame::OnSystemEmployee)
	ON_UPDATE_COMMAND_UI(ID_SYSTEM_EMPLOYEE, &CMainFrame::OnUpdateSystemEmployee)
	ON_COMMAND(ID_USER_INFOEDIT, &CMainFrame::OnUserInfoedit)
	ON_COMMAND(ID_USER_OPENCARD, &CMainFrame::OnUserOpencard)
	ON_COMMAND(ID_USER_PRESTORE, &CMainFrame::OnUserPrestore)
	ON_COMMAND(ID_USER_REFUND, &CMainFrame::OnUserRefund)
	ON_COMMAND(ID_USER_RETURNDEPOSIT, &CMainFrame::OnUserReturndeposit)
	ON_COMMAND(ID_USER_CLOSECARD, &CMainFrame::OnUserClosecard)
	ON_COMMAND(ID_USER_INFOQUERY, &CMainFrame::OnUserInfoquery)
	ON_COMMAND(ID_USER_LOGQUERY, &CMainFrame::OnUserLogquery)
	ON_COMMAND(ID_USER_INCOMESTATISTICS, &CMainFrame::OnUserIncomestatistics)
	ON_COMMAND(ID_USER_PRESTORESTATISTICS, &CMainFrame::OnUserPrestorestatistics)
	ON_MESSAGE(WM_MSGRECVPRO, &CMainFrame::OnMsgrecvpro)
	ON_COMMAND(ID_TOOL_READCARD, &CMainFrame::OnToolReadcard)
	ON_COMMAND(ID_TOOL_LICENSECARD, &CMainFrame::OnToolLicensecard)
	ON_COMMAND(ID_TOOL_SETCARD, &CMainFrame::OnToolSetcard)
	ON_COMMAND(ID_SYSTEM_PASSWORD, &CMainFrame::OnSystemPassword)
	ON_COMMAND(ID_TOOL_CLEARCARD, &CMainFrame::OnToolClearcard)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_PROGRESS,
	ID_INDICATOR_EMPLOYEE,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
	: m_p_eeDlg(NULL)
	, m_p_uieDlg(NULL)
	, m_p_upDlg(NULL)
	, m_p_urDlg(NULL)
	, m_p_urdDlg(NULL)
	, m_p_uccDlg(NULL)
	, m_p_uiqDlg(NULL)
	, m_p_ulqDlg(NULL)
	, m_p_uisDlg(NULL)
	, m_p_upsDlg(NULL)
	, m_p_treadcDlg(NULL)
	, m_p_tlicensecDlg(NULL)
	, m_p_tsetcDlg(NULL)
	, m_p_tcclearcDlg(NULL)
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_WINDOWS_7);
}

CMainFrame::~CMainFrame()
{
	if (m_p_uieDlg)
		delete m_p_uieDlg;
	if (m_p_eeDlg)
		delete m_p_eeDlg;
	if (m_p_upDlg)
		delete m_p_upDlg;
	if (m_p_urDlg)
		delete m_p_urDlg;
	if (m_p_urdDlg)
		delete m_p_urdDlg;
	if (m_p_uccDlg)
		delete m_p_uccDlg;
	if (m_p_uiqDlg)
		delete m_p_uiqDlg;
	if (m_p_ulqDlg)
		delete m_p_ulqDlg;
	if (m_p_uisDlg)
		delete m_p_uisDlg;
	if (m_p_upsDlg)
		delete m_p_upsDlg;
	if (m_p_treadcDlg)
		delete m_p_treadcDlg;
	if (m_p_tlicensecDlg)
		delete m_p_tlicensecDlg;
	if (m_p_tsetcDlg)
		delete m_p_tsetcDlg;
	if (m_p_tcclearcDlg)
		delete m_p_tcclearcDlg;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("未能创建菜单栏\n");
		return -1;      // 未能创建
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// 防止菜单栏在激活时获得焦点
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	CString strToolBarName;
	bNameValid = strToolBarName.LoadString(IDS_TOOLBAR_STANDARD);
	ASSERT(bNameValid);
	m_wndToolBar.SetWindowText(strToolBarName);
	m_wndToolBar.EnableTextLabels(TRUE);//工具栏同时显示图标和文字

	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);
	m_wndToolBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);

	// 允许用户定义的工具栏操作: 
	InitUserToolbars(nullptr, uiFirstUserToolBarId, uiLastUserToolBarId);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	
	// TODO: 如果您不希望工具栏和菜单栏可停靠，请删除这五行
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);


	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	// 启用工具栏和停靠窗口菜单替换
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, strCustomize, ID_VIEW_TOOLBAR);

	// 启用快速(按住 Alt 拖动)工具栏自定义
	CMFCToolBar::EnableQuickCustomization();

	if (CMFCToolBar::GetUserImages() == nullptr)
	{
		// 加载用户定义的工具栏图像
		if (m_UserImages.Load(_T(".\\UserImages.bmp")))
		{
			CMFCToolBar::SetUserImages(&m_UserImages);
		}
	}

	// 启用菜单个性化(最近使用的命令)
	// TODO: 定义您自己的基本命令，确保每个下拉菜单至少有一个基本命令。
	CList<UINT, UINT> lstBasicCommands;

	lstBasicCommands.AddTail(ID_SYSTEM_EMPLOYEE);
	lstBasicCommands.AddTail(ID_SYSTEM_PASSWORD);
	lstBasicCommands.AddTail(ID_FILE_PRINT_SETUP);
	lstBasicCommands.AddTail(ID_APP_EXIT);
	lstBasicCommands.AddTail(ID_USER_INFOEDIT);
	lstBasicCommands.AddTail(ID_USER_OPENCARD);
	lstBasicCommands.AddTail(ID_USER_PRESTORE);
	lstBasicCommands.AddTail(ID_USER_REFUND);
	lstBasicCommands.AddTail(ID_USER_RETURNDEPOSIT);
	lstBasicCommands.AddTail(ID_USER_CLOSECARD);
	lstBasicCommands.AddTail(ID_USER_INFOQUERY);
	lstBasicCommands.AddTail(ID_USER_LOGQUERY);
	lstBasicCommands.AddTail(ID_USER_INCOMESTATISTICS);
	lstBasicCommands.AddTail(ID_USER_PRESTORESTATISTICS);
	lstBasicCommands.AddTail(ID_TOOL_READCARD);
	lstBasicCommands.AddTail(ID_TOOL_LICENSECARD);
	lstBasicCommands.AddTail(ID_TOOL_SETCARD);
	lstBasicCommands.AddTail(ID_TOOL_CLEARCARD);
	lstBasicCommands.AddTail(ID_APP_ABOUT);
	lstBasicCommands.AddTail(ID_VIEW_STATUS_BAR);
	lstBasicCommands.AddTail(ID_VIEW_TOOLBAR);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2003);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_VS_2005);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLUE);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_SILVER);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_BLACK);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_OFF_2007_AQUA);
	lstBasicCommands.AddTail(ID_VIEW_APPLOOK_WINDOWS_7);

	CMFCToolBar::SetBasicCommands(lstBasicCommands);

	InitInCreate();
	g_sz_p_wnd[WND_MAINFRAME] = this;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* 扫描菜单*/);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*)lres;
	ASSERT_VALID(pUserToolbar);

	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
	return lres;
}

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(nullptr, nullptr, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
	// 基类将执行真正的工作

	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}


	// 为所有用户工具栏启用自定义按钮
	BOOL bNameValid;
	CString strCustomize;
	bNameValid = strCustomize.LoadString(IDS_TOOLBAR_CUSTOMIZE);
	ASSERT(bNameValid);

	for (int i = 0; i < iMaxUserToolbars; i ++)
	{
		CMFCToolBar* pUserToolbar = GetUserToolBarByIndex(i);
		if (pUserToolbar != nullptr)
		{
			pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, strCustomize);
		}
	}

	return TRUE;
}


void CMainFrame::OnSystemEmployee()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_p_eeDlg)
	{
		m_p_eeDlg = new CEmployeeEdit();
		m_p_eeDlg->Create(IDD_EMPLOYEEEDIT, this);
	}
	m_p_eeDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnUpdateSystemEmployee(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	switch (g_employee.GetGradeID())
	{
	case 0:pCmdUI->Enable(TRUE);; break;
	case 1:pCmdUI->Enable(FALSE);; break;
	}
}


void CMainFrame::OnSystemPassword()
{
	// TODO: 在此添加命令处理程序代码
	CPasswordEdit peDlg;
	peDlg.DoModal();
}


void CMainFrame::OnUserInfoedit()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_p_uieDlg)
	{
		m_p_uieDlg = new CUserInfoEdit();
		m_p_uieDlg->Create(IDD_USERINFOEDIT, this);
	}
	m_p_uieDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnUserOpencard()
{
	// TODO: 在此添加命令处理程序代码
	//m_p_uocDlg->ShowWindow(SW_SHOW);
	CUserOpenCard uocDlg;
	uocDlg.DoModal();
}


void CMainFrame::OnUserPrestore()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_p_upDlg)
	{
		m_p_upDlg = new CUserPrestore();
		m_p_upDlg->Create(IDD_USERPRESTORE, this);
	}
	m_p_upDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnUserRefund()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_p_urDlg)
	{
		m_p_urDlg = new CUserRefund();
		m_p_urDlg->Create(IDD_USERREFUND, this);
	}
	m_p_urDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnUserReturndeposit()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_p_urdDlg)
	{
		m_p_urdDlg = new CUserReturnDeposit();
		m_p_urdDlg->Create(IDD_USERRETURNDEPOSIT, this);
	}
	m_p_urdDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnUserClosecard()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_p_uccDlg)
	{
		m_p_uccDlg = new CUserCloseCard();
		m_p_uccDlg->Create(IDD_USERCLOSECARD, this);
	}
	m_p_uccDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnUserInfoquery()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_p_uiqDlg)
	{
		m_p_uiqDlg = new CUserInfoQuery();
		m_p_uiqDlg->Create(IDD_USERINFOQUERY, this);
	}
	m_p_uiqDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnUserLogquery()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_p_ulqDlg)
	{
		m_p_ulqDlg = new CUserLogQuery();
		m_p_ulqDlg->Create(IDD_USERLOGQUERY, this);
	}
	m_p_ulqDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnUserIncomestatistics()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_p_uisDlg)
	{
		m_p_uisDlg = new CUserIncomeStatistics();
		m_p_uisDlg->Create(IDD_USERINCOMESTATISTICS, this);
	}
	m_p_uisDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnUserPrestorestatistics()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_p_upsDlg)
	{
		m_p_upsDlg = new CUserPrestoreStatistics();
		m_p_upsDlg->Create(IDD_USERPRESTORESTATISTICS, this);
	}
	m_p_upsDlg->ShowWindow(SW_SHOW);
}



afx_msg LRESULT CMainFrame::OnMsgrecvpro(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case MSGUSER_UPDATEPROGRESS:
	{
		m_wndStatusBar.SetPaneProgress(1, wParam);
	}
	break;
	}
	return 0;
}


void CMainFrame::InitInCreate()
{
	// TODO: 在此处添加实现代码.
	CString strEmployeeInfo;
	strEmployeeInfo.Format(_T("工号：%d  姓名：%s"), g_employee.GetID(), g_employee.GetName());
	m_wndStatusBar.EnablePaneProgressBar(1, 100, TRUE);
	m_wndStatusBar.SetPaneWidth(1, 500);
	m_wndStatusBar.SetPaneProgress(1,0);
	m_wndStatusBar.SetPaneText(2, strEmployeeInfo);
	m_wndStatusBar.SetPaneTextColor(2, RGB(255, 0, 0));
	/*if (!m_p_uocDlg)
	{
		m_p_uocDlg = new CUserOpenCard();
		m_p_uocDlg->Create(IDD_USEROPENCARD, this);
	}*/
}


void CMainFrame::OnToolReadcard()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_p_treadcDlg)
	{
		m_p_treadcDlg = new CToolReadCard();
		m_p_treadcDlg->Create(IDD_TOOLREADCARD, this);
	}
	m_p_treadcDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnToolLicensecard()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_p_tlicensecDlg)
	{
		m_p_tlicensecDlg = new CToolLicenseCard();
		m_p_tlicensecDlg->Create(IDD_TOOLLICENSECARD, this);
	}
	m_p_tlicensecDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnToolSetcard()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_p_tsetcDlg)
	{
		m_p_tsetcDlg = new CToolSetCard();
		m_p_tsetcDlg->Create(IDD_TOOLSETCARD,this);
	}
	m_p_tsetcDlg->ShowWindow(SW_SHOW);
}


void CMainFrame::OnToolClearcard()
{
	// TODO: 在此添加命令处理程序代码
	if (!m_p_tcclearcDlg)
	{
		m_p_tcclearcDlg = new CToolClearCard();
		m_p_tcclearcDlg->Create(IDD_TOOLCLEARCARD, this);
	}
	m_p_tcclearcDlg->ShowWindow(SW_SHOW);
}
