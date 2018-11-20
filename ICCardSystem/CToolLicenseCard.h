#pragma once


// CToolLicenseCard 对话框

class CToolLicenseCard : public CDialogEx
{
	DECLARE_DYNAMIC(CToolLicenseCard)

public:
	CToolLicenseCard(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CToolLicenseCard();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLLICENSECARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonLicensecard();
	afx_msg void OnEnChangeEditLicense();
};
