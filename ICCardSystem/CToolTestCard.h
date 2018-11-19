#pragma once


// CToolTestCard 对话框

class CToolTestCard : public CDialogEx
{
	DECLARE_DYNAMIC(CToolTestCard)

public:
	CToolTestCard(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CToolTestCard();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLTESTCARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonTestcard();
};
