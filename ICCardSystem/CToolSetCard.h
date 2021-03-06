#pragma once


// CToolSetCard 对话框

class CToolSetCard : public CDialogEx
{
	DECLARE_DYNAMIC(CToolSetCard)

public:
	CToolSetCard(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CToolSetCard();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLSETCARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSetcard();
	afx_msg void OnEnChangeEditLicense();
	afx_msg void OnEnChangeEditRupturecurrent();
	afx_msg void OnEnChangeEditPortnum();
	afx_msg void OnEnChangeEditChargetime();
	afx_msg void OnEnChangeEditRatedcurrent();
	afx_msg void OnEnChangeEditUnitprice();
};
