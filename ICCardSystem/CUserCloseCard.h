#pragma once


// CUserCloseCard 对话框

class CUserCloseCard : public CDialogEx
{
	DECLARE_DYNAMIC(CUserCloseCard)

public:
	CUserCloseCard(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUserCloseCard();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERCLOSECARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CEdit m_editID;
	CEdit m_editName;
	CEdit m_editIDNo;
	CEdit m_editPhoneNo;
	CEdit m_editAddr;
	CEdit m_editLicense;
	CEdit m_editState;
	CEdit m_editCardNo;
	CEdit m_editBalance;
	CEdit m_editDeposit;
	CEdit m_editAmount;
	CUser m_SelectUser;
	CUserDB m_udb;
	CCard m_SelectCard;
	CCardDB m_cdb;
	int m_nDeposit;
	CRefundRecordDB m_rrdb;
	CReturnDepositRecordDB m_rdrdb;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonReadcard();
	afx_msg void OnBnClickedButtonClosecard();
	void GetDeposit(const CUser & user, const CCard & card);
	void InsertEdit(const CUser & user, const CCard & card);
};
