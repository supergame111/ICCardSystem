#include "stdafx.h"
#include "CEmployee.h"


CEmployee::CEmployee()
{
	
}


CEmployee::CEmployee(int nID, CString strName, CString strPassword, int nGradeID, BOOL nIsUsing)
	: m_nID(nID)
	, m_strName(strName)
	, m_strPassword(strPassword)
	, m_nGradeID(nGradeID)
	, m_nIsUsing(nIsUsing)
{
}

CEmployee::~CEmployee()
{
}


int CEmployee::GetID() const
{
	return m_nID;
}


CString CEmployee::GetName() const
{
	return m_strName;
}


CString CEmployee::GetPassword() const
{
	return m_strPassword;
}


int CEmployee::GetGradeID() const
{
	return m_nGradeID;
}


BOOL CEmployee::IsUsing() const
{
	return m_nIsUsing;
}


void CEmployee::SetPassword(const CString & strPassword)
{
	m_strPassword = strPassword;
}