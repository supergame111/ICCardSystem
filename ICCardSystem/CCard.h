#pragma once
class CCard
{
public:
	enum TYPE
	{
		TYPE_MONTHLY = 0,
		TYPE_RECHARGE
	};
private:
	int m_nID;
	int m_nUserID;
	int m_nNo;//卡号
	int m_nType;//类型
	CString m_strDeadline;//截至日期
	int m_nDeposit;//单位:分
	int m_nEmployeeIDOpenCard;
	CString m_strTimeOpenCard;
	int m_nEmployeeIDCloseCard;
	CString m_strTimeCloseCard;
public:
	CCard();
	CCard(int nID, int nUserID, int nNo, int nType, CString strDeadline, int nDeposit, int nEmployeeIDOpenCard, CString strTimeOpenCard, int nEmployeeIDCloseCard, CString strTimeCloseCard);
	virtual ~CCard();
	int GetID() const;
	int GetUserID() const;
	int GetNo() const;
	int GetType() const;
	CString GetDeadline() const;
	int GetDeposit() const;
	int GetEmployeeIDOpenCard() const;
	CString GetTimeOpenCard() const;
	int GetEmployeeIDCloseCard() const;
	CString GetTimeCloseCard() const;
	void SetID(int nID);
	void SetUserID(int nUserID);
	void SetNo(int nNo);
	void SetType(int nType);
	void SetDeadline(CString strDeadline);
	void SetDeposit(int nDeposit);
	void SetEmployeeIDOpenCard(int nEmployeeIDOpenCard);
	void SetTimeOpenCard(CString strTimeOpenCard);
	void SetEmployeeIDCloseCard(int nEmployeeIDCloseCard);
	void SetTimeCloseCard(CString strTimeCloseCard);
};

