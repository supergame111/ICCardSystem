#pragma once


// CPasswordEdit 对话框

class CPasswordEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CPasswordEdit)

public:
	CPasswordEdit(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPasswordEdit();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PASSWORDEDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonModify();
};
