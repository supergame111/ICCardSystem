#pragma once


// CToolReadCard 对话框

class CToolReadCard : public CDialogEx
{
	DECLARE_DYNAMIC(CToolReadCard)

public:
	CToolReadCard(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CToolReadCard();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLREADCARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonReadcard();
};
