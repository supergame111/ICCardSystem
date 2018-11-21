#include "stdafx.h"
#include "CUser.h"


CUser::CUser()
	:m_nID(0)
	,m_nState(STATE_UNOPEN)
{
}


CUser::CUser(int nID,CString strName,CString strIDNo,CString strPhoneNo,CString strAddr,int nLicense,int nTotalAmount,int nState,CString strNoteInfo, int nEmployeeIDAdd, CString strTimeAdd, int nEmployeeIDLastModify, CString strTimeLastModify)
	: m_nID(nID)
	, m_strName(strName)
	, m_strIDNo(strIDNo)
	, m_strPhoneNo(strPhoneNo)
	, m_strAddr(strAddr)
	, m_nLicense(nLicense)
	, m_nTotalAmount(nTotalAmount)
	, m_nState(STATE_UNOPEN)
	, m_strNoteInfo(strNoteInfo)
	, m_nEmployeeIDAdd(nEmployeeIDAdd)
	, m_strTimeAdd(strTimeAdd)
	, m_nEmployeeIDLastModify(nEmployeeIDLastModify)
	, m_strTimeLastModify(strTimeLastModify)
{
	if (nState < STATE_ERROR)
		m_nState = nState;
}

CUser::~CUser()
{
}


int CUser::GetID() const
{
	return m_nID;
}


CString CUser::GetName() const
{
	return m_strName;
}


CString CUser::GetIDNo() const
{
	return m_strIDNo;
}


CString CUser::GetPhoneNo() const
{
	return m_strPhoneNo;
}


CString CUser::GetAddr() const
{
	return m_strAddr;
}


int CUser::GetLicense() const
{
	return m_nLicense;
}


int CUser::GetTotalAmount() const
{
	return m_nTotalAmount;
}


int CUser::GetState() const
{
	return m_nState;
}


CString CUser::GetNoteInfo() const
{
	return m_strNoteInfo;
}


int CUser::GetEmployeeIDAdd() const
{
	return m_nEmployeeIDAdd;
}


CString CUser::GetTimeAdd() const
{
	return m_strTimeAdd;
}


int CUser::GetEmployeeIDLastModify() const
{
	return m_nEmployeeIDLastModify;
}


CString CUser::GetTimeLastModify() const
{
	return m_strTimeLastModify;
}


void CUser::SetID(int nID)
{
	m_nID = nID;
}


void CUser::SetName(const CString & strName)
{
	m_strName = strName;
}


void CUser::SetIDNo(const CString & strIDNo)
{
	m_strIDNo = strIDNo;
}


void CUser::SetPhoneNo(const CString & strPhoneNo)
{
	m_strPhoneNo = strPhoneNo;
}


void CUser::SetAddr(const CString & strAddr)
{
	m_strAddr = strAddr;
}


void CUser::SetLicense(int nLicense)
{
	m_nLicense = nLicense;
}


void CUser::SetTotalAmount(int nTotalAmount)
{
	m_nTotalAmount = nTotalAmount;
}


void CUser::SetState(int nState)
{
	if(nState< STATE_ERROR)
		m_nState = nState;
}


void CUser::SetNoteInfo(const CString & strNoteInfo)
{
	m_strNoteInfo = strNoteInfo;
}


void CUser::SetEmployeeIDAdd(int nEmployeeIDAdd)
{
	m_nEmployeeIDAdd = nEmployeeIDAdd;
}


void CUser::SetTimeAdd(const CString & strTimeAdd)
{
	m_strTimeAdd = strTimeAdd;
}


void CUser::SetEmployeeIDLastModify(int nEmployeeIDLastModify)
{
	m_nEmployeeIDLastModify = nEmployeeIDLastModify;
}


void CUser::SetTimeLastModify(const CString & strTimeLastModify)
{
	m_strTimeLastModify = strTimeLastModify;
}