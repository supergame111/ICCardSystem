#pragma once


// CToolResetCard 对话框

class CToolResetCard : public CDialogEx
{
	DECLARE_DYNAMIC(CToolResetCard)

public:
	CToolResetCard(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CToolResetCard();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLRESETCARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonResetcard();
};
