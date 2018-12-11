#pragma once


// CToolClearCard 对话框

class CToolClearCard : public CDialogEx
{
	DECLARE_DYNAMIC(CToolClearCard)

public:
	CToolClearCard(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CToolClearCard();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLCLEARCARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonClearcard();
	afx_msg void OnEnChangeEditLicense();
	afx_msg void OnEnChangeEditUsagecount();
};
