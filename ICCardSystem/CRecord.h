#pragma once
class CRecord
{
private:
	int m_nID;
	int m_nUserID;
	int m_nCardNo;
	int m_nAmountOld;
	int m_nAmount;
	int m_nAmountNew;
	int m_nDeposit;
	CString m_strNoteInfo;
	int m_nEmployeeID;
	CString m_strTime;
public:
	CRecord();
	CRecord(int nID,int nUserID, int nCardNo,int nAmountOld, int nAmount, int nAmountNew, int nDeposit, CString strNoteInfo,int nEmployeeID,CString strTime);
	virtual ~CRecord();
	int GetID() const;
	int GetUserID() const;
	int GetCardNo() const;
	int GetAmountOld() const;
	int GetAmount() const;
	int GetAmountNew() const;
	int GetDeposit() const;
	CString GetNoteInfo() const;
	int GetEmployeeID() const;
	CString GetTime() const;
};

