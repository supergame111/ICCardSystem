#pragma once
class CUser
{
public:
	enum STATE 
	{
		STATE_UNOPEN=0,
		STATE_OPEN,
		STATE_CLOSE,
		STATE_ERROR
	};
private:
	int m_nID;
	CString m_strName;
	CString m_strIDNo;
	CString m_strPhoneNo;
	CString m_strAddr;
	int m_nLicense;
	int m_nTotalAmount;//µ¥Î»:·Ö
	int m_nState;
	CString m_strNoteInfo;
	int m_nEmployeeIDAdd;
	CString m_strTimeAdd;
	int m_nEmployeeIDLastModify;
	CString m_strTimeLastModify;
public:
	CUser();
	CUser(int nID, CString strName, CString strIDNo, CString strPhoneNo, CString strAddr, int nLicense, int nTotalAmount,  int nState, CString strNoteInfo, int nEmployeeIDAdd, CString strTimeAdd, int nEmployeeIDLastModify, CString strTimeLastModify);
	virtual ~CUser();
	int GetID() const;
	CString GetName() const;
	CString GetIDNo() const;
	CString GetPhoneNo() const;
	CString GetAddr() const;
	int GetLicense() const;
	int GetTotalAmount() const;
	int GetState() const;
	CString GetNoteInfo() const;
	int GetEmployeeIDAdd() const;
	CString GetTimeAdd() const;
	int GetEmployeeIDLastModify() const;
	CString GetTimeLastModify() const;
	void SetID(int nID);
	void SetName(const CString & strName);
	void SetIDNo(const CString & strIDNo);
	void SetPhoneNo(const CString & strPhoneNo);
	void SetAddr(const CString & strAddr);
	void SetLicense(int nLicense);
	void SetTotalAmount(int nTotalAmount);
	void SetState(int nState);
	void SetNoteInfo(const CString & strNoteInfo);
	void SetEmployeeIDAdd(int nEmployeeIDAdd);
	void SetTimeAdd(const CString & strTimeAdd);
	void SetEmployeeIDLastModify(int nEmployeeIDLastModify);
	void SetTimeLastModify(const CString & strTimeLastModify);
};

