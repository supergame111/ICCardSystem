#pragma once


// CUserPrestoreStatistics 对话框

class CUserPrestoreStatistics : public CDialogEx, public ZExcelExport::CCallBack
{
	DECLARE_DYNAMIC(CUserPrestoreStatistics)

public:
	CUserPrestoreStatistics(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUserPrestoreStatistics();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERPRESTORESTATISTICS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CListCtrl m_listctrlUser;
	CEdit m_editYear;
	bool m_bIsInitFinish;
	CString m_strTtitle;
	CString m_strSubTtitle;
protected:
	afx_msg LRESULT OnMsgrecvpro(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonStatistics();
	afx_msg void OnBnClickedButtonPrint();
	afx_msg void OnBnClickedButtonExport();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	void InitUI();
	void GetUser(std::vector<CUser> & vec_user);
	void GetData(const CUser & user);
	void UpdateList(std::vector<std::vector<CString>> & vec2_strData);
	virtual void OnExportProgressUpdate(int nProgress);
	virtual void OnExportResult(bool bResult);
};
