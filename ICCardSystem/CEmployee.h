#pragma once
class CEmployee
{
private:
	int m_nID;
	CString m_strName;
	CString m_strPassword;
	int m_nGradeID;
	BOOL m_nIsUsing;
public:
	CEmployee();
	CEmployee(int nID, CString strName,CString strPassword, int nGradeID,BOOL nIsUsing);
	virtual ~CEmployee();
	int GetID() const;
	CString GetName() const;
	CString GetPassword() const;
	int GetGradeID() const;
	BOOL IsUsing() const;
	void SetPassword(const CString & strPassword);
};

