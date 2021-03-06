#pragma once


// CUserRefund 对话框

class CUserRefund : public CDialogEx
{
	DECLARE_DYNAMIC(CUserRefund)

public:
	CUserRefund(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUserRefund();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERREFUND };
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
	CEdit m_editBalance;
	CEdit m_editCardNo;
	CEdit m_editAmount;
	CEdit m_editBalanceNew;
	CEdit m_editLastAmount;
	CEdit m_editTotalAmount;
	CEdit m_editPrestoreTimes;
	CEdit m_editNoteInfo;
	CUser m_SelectUser;
	CUserDB m_udb;
	CCard m_SelectCard;
	CCardDB m_cdb;
	int m_nDeposit;
	CPrestoreRecordDB m_prdb;
	CRefundRecordDB m_rrdb;
	CReturnDepositRecordDB m_rdrdb;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonReadcard();
	afx_msg void OnBnClickedButtonRefund();
	afx_msg void OnEnChangeEditAmount();
	void GetDeposit(const CUser & user, const CCard & card);
	void InsertEdit(const CUser & user, const CCard & card);
};
