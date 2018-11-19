#pragma once


// CToolQueryCard 对话框

class CToolQueryCard : public CDialogEx
{
	DECLARE_DYNAMIC(CToolQueryCard)

public:
	CToolQueryCard(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CToolQueryCard();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLQUERYCARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonQuerycard();
};
