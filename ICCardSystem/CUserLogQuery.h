#pragma once


// CUserLogQuery 对话框

class CUserLogQuery : public CDialogEx, public ZExcelExport::CCallBack
{
	DECLARE_DYNAMIC(CUserLogQuery)

public:
	CUserLogQuery(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUserLogQuery();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERLOGQUERY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_comboCondition;
	CListCtrl m_listctrlUser;
	CEdit m_editKeyword;
	CComboBox m_comboItem;
	CDateTimeCtrl m_datetimeStart;
	CDateTimeCtrl m_datetimeEnd;
	bool m_bIsInitFinish;
	CString m_strTtitle;
	CString m_strSubTtitle;
protected:
	afx_msg LRESULT OnMsgrecvpro(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonPrint();
	afx_msg void OnBnClickedButtonExport();
	afx_msg void OnBnClickedRadioThisyear();
	afx_msg void OnBnClickedRadioLastyear();
	afx_msg void OnBnClickedRadioThismonth();
	afx_msg void OnBnClickedRadioLastmonth();
	afx_msg void OnBnClickedRadioToday();
	afx_msg void OnBnClickedRadioYesterday();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	void InitUI();
	CString GetSqlSelect(int nSelItem,CString & strTableLeft);
	CString GetSqlWhere(int nSelCondition,const CString & strTableLeft);
	void UpdateList(std::vector<std::vector<CString>> & vec2_strData);
	virtual void OnExportProgressUpdate(int nProgress);
	virtual void OnExportResult(bool bResult);
};
