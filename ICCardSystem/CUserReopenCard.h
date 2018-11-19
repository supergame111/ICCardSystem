#pragma once


// CUserReopenCard 对话框

class CUserReopenCard : public CDialogEx
{
	DECLARE_DYNAMIC(CUserReopenCard)

public:
	CUserReopenCard(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUserReopenCard();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERREOPENCARD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_comboCondition;
	CListCtrl m_listctrlUser;
	CEdit m_editKeyword;
	CEdit m_editID;
	CEdit m_editName;
	CEdit m_editIDNo;
	CEdit m_editPhoneNo;
	CEdit m_editAddr;
	CEdit m_editLicense;
	CEdit m_editUnitName;
	CEdit m_editLastAmount;
	CEdit m_editTotalAmount;
	CEdit m_editPrestoreTimes;
	CEdit m_editAmount;
	CEdit m_editCardNo;
	CEdit m_editNoteInfo;
	CUserDB m_udb;
	CUser m_SelectUser;
	int m_nDeposit;
	CPrestoreRecordDB m_prdb;
	CReopenCardRecordDB m_rcrdb;
	CReturnDepositRecordDB m_rdrdb;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonReopencard();
	afx_msg void OnBnClickedButtonPrestore();
	afx_msg void OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult);
	void InitUI();
	void UpdateList(const std::vector<CUser> & vec_user);
	void GetDeposit(const CUser & user);
	void InsertEdit(const CUser & user);
	void InsertEditByID(int nID);
};
