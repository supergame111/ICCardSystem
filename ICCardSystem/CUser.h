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
	int m_nUnitID;
	CString m_strUnitName;
	int m_nDeviceID;
	int m_nTotalAmount;//单位:分
	int m_nDeposit;//单位:分
	int m_nState;
	CString m_strNoteInfo;
	int m_nEmployeeIDOpenCard;
	CString m_strTimeOpenCard;
	int m_nEmployeeIDCloseCard;
	CString m_strTimeCloseCard;
	int m_nEmployeeIDAdd;
	CString m_strTimeAdd;
	int m_nEmployeeIDLastModify;
	CString m_strTimeLastModify;
public:
	CUser();
	CUser(int nID, CString strName, CString strIDNo, CString strPhoneNo, CString strAddr, int nUnitID, CString strUnitName, int nDeviceID, int nTotalAmount, int nDeposit, int nState, CString strNoteInfo, int nEmployeeIDOpenCard, CString strTimeOpenCard,  int nEmployeeIDCloseCard, CString strTimeCloseCard, int nEmployeeIDAdd, CString strTimeAdd, int nEmployeeIDLastModify, CString strTimeLastModify);
	virtual ~CUser();
	int GetID() const;
	CString GetName() const;
	CString GetIDNo() const;
	CString GetPhoneNo() const;
	CString GetAddr() const;
	int GetUnitID() const;
	CString GetUnitName() const;
	int GetDeviceID() const;
	int GetTotalAmount() const;
	int GetDeposit() const;
	int GetState() const;
	CString GetNoteInfo() const;
	int GetEmployeeIDOpenCard() const;
	CString GetTimeOpenCard() const;
	int GetEmployeeIDCloseCard() const;
	CString GetTimeCloseCard() const;
	int GetEmployeeIDAdd() const;
	CString GetTimeAdd() const;
	int GetEmployeeIDLastModify() const;
	CString GetTimeLastModify() const;
	void SetID(int nID);
	void SetName(const CString & strName);
	void SetIDNo(const CString & strIDNo);
	void SetPhoneNo(const CString & strPhoneNo);
	void SetAddr(const CString & strAddr);
	void SetUnitID(int nUnitID);
	void SetUnitName(const CString & strUnitName);
	void SetDeviceID(int nDeviceID);
	void SetTotalAmount(int nTotalAmount);
	void SetDeposit(int nDeposit);
	void SetState(int nState);
	void SetNoteInfo(const CString & strNoteInfo);
	void SetEmployeeIDOpenCard(int nEmployeeIDOpenCard);
	void SetTimeOpenCard(const CString & strTimeOpenCard);
	void SetEmployeeIDCloseCard(int nEmployeeIDOpenCard);
	void SetTimeCloseCard(const CString & strTimeOpenCard);
	void SetEmployeeIDAdd(int nEmployeeIDAdd);
	void SetTimeAdd(const CString & strTimeAdd);
	void SetEmployeeIDLastModify(int nEmployeeIDLastModify);
	void SetTimeLastModify(const CString & strTimeLastModify);
};

