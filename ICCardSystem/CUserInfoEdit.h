#pragma once


// CUserInfoEdit 对话框

class CUserInfoEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CUserInfoEdit)

public:
	CUserInfoEdit(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUserInfoEdit();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERINFOEDIT };
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
	CEdit m_editTotalAmount;
	CEdit m_editState;
	CEdit m_editNoteInfo;
	CUserDB m_udb;
	std::vector<CEdit *> m_vec_edit;
	bool m_bSaveFromAdd;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonOpencard();
	afx_msg void OnNMClickListUser(NMHDR *pNMHDR, LRESULT *pResult);
	void InitUI();
	void InitEdit();
	void UpdateList(const std::vector<CUser> & vec_user);
	void GetEditText(std::vector<CString> & vec_str);
	void SetEditEmpty();
	void SetIntoEdit();
	void SetOutOfEdit();
	void InsertEdit(const CUser & user);
	void InsertEditByID(int nID);
};
