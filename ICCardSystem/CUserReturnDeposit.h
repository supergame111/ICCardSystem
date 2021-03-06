#pragma once


// CUserReturnDeposit 对话框

class CUserReturnDeposit : public CDialogEx
{
	DECLARE_DYNAMIC(CUserReturnDeposit)

public:
	CUserReturnDeposit(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUserReturnDeposit();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERRETURNDEPOSIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
private:
	CEdit m_editID;
	CEdit m_editName;
	CEdit m_editIDNo;
	CEdit m_editPhoneNo;
	CEdit m_editAddr;
	CEdit m_editLicense;
	CEdit m_editState;
	CEdit m_editDeposit;
	CEdit m_editCardNo;
	CEdit m_editAmount;
	CEdit m_editDepositNew;
	CEdit m_editNoteInfo;
	CUser m_SelectUser;
	CUserDB m_udb;
	CCard m_SelectCard;
	CCardDB m_cdb;
	int m_nDeposit;
	CReturnDepositRecordDB m_rdrdb;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonReadcard();
	afx_msg void OnBnClickedButtonReturndeposit();
	afx_msg void OnEnChangeEditAmount();
	void GetDeposit(const CUser & user, const CCard & card);
	void InsertEdit(const CUser & user, const CCard & card);
};
