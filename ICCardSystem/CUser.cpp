#include "stdafx.h"
#include "CUser.h"


CUser::CUser()
{
}


CUser::CUser(int nID,CString strName,CString strIDNo,CString strPhoneNo,CString strAddr,int nUnitID,CString strUnitName,int nDeviceID,int nTotalAmount,int nDeposit,int nState,CString strNoteInfo, int nEmployeeIDOpenCard, CString strTimeOpenCard, int nEmployeeIDCloseCard, CString strTimeCloseCard, int nEmployeeIDAdd, CString strTimeAdd, int nEmployeeIDLastModify, CString strTimeLastModify)
	: m_nID(nID)
	, m_strName(strName)
	, m_strIDNo(strIDNo)
	, m_strPhoneNo(strPhoneNo)
	, m_strAddr(strAddr)
	, m_nUnitID(nUnitID)
	, m_strUnitName(strUnitName)
	, m_nDeviceID(nDeviceID)
	, m_nTotalAmount(nTotalAmount)
	, m_nDeposit(nDeposit)
	, m_nState(nState)
	, m_strNoteInfo(strNoteInfo)
	, m_nEmployeeIDOpenCard(nEmployeeIDOpenCard)
	, m_strTimeOpenCard(strTimeOpenCard)
	, m_nEmployeeIDCloseCard(nEmployeeIDCloseCard)
	, m_strTimeCloseCard(strTimeCloseCard)
	, m_nEmployeeIDAdd(nEmployeeIDAdd)
	, m_strTimeAdd(strTimeAdd)
	, m_nEmployeeIDLastModify(nEmployeeIDLastModify)
	, m_strTimeLastModify(strTimeLastModify)
{
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


int CUser::GetUnitID() const
{
	return m_nUnitID;
}


CString CUser::GetUnitName() const
{
	return m_strUnitName;
}


int CUser::GetDeviceID() const
{
	return m_nDeviceID;
}


int CUser::GetTotalAmount() const
{
	return m_nTotalAmount;
}


int CUser::GetDeposit() const
{
	return m_nDeposit;
}


int CUser::GetState() const
{
	return m_nState;
}


CString CUser::GetNoteInfo() const
{
	return m_strNoteInfo;
}


int CUser::GetEmployeeIDOpenCard() const
{
	return m_nEmployeeIDOpenCard;
}


CString CUser::GetTimeOpenCard() const
{
	return m_strTimeOpenCard;
}


int CUser::GetEmployeeIDCloseCard() const
{
	return m_nEmployeeIDCloseCard;
}


CString CUser::GetTimeCloseCard() const
{
	return m_strTimeCloseCard;
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


void CUser::SetUnitID(int nUnitID)
{
	m_nUnitID = nUnitID;
}


void CUser::SetUnitName(const CString & strUnitName)
{
	m_strUnitName = strUnitName;
}


void CUser::SetDeviceID(int nDeviceID)
{
	m_nDeviceID = nDeviceID;
}


void CUser::SetTotalAmount(int nTotalAmount)
{
	m_nTotalAmount = nTotalAmount;
}


void CUser::SetDeposit(int nDeposit)
{
	m_nDeposit = nDeposit;
}


void CUser::SetState(int nState)
{
	if(nState< CUser::STATE_ERROR)
		m_nState = nState;
}


void CUser::SetNoteInfo(const CString & strNoteInfo)
{
	m_strNoteInfo = strNoteInfo;
}


void CUser::SetEmployeeIDOpenCard(int nEmployeeIDOpenCard)
{
	m_nEmployeeIDOpenCard = nEmployeeIDOpenCard;
}


void CUser::SetTimeOpenCard(const CString & strTimeOpenCard)
{
	m_strTimeOpenCard = strTimeOpenCard;
}


void CUser::SetEmployeeIDCloseCard(int nEmployeeIDCloseCard)
{
	m_nEmployeeIDCloseCard = nEmployeeIDCloseCard;
}


void CUser::SetTimeCloseCard(const CString & strTimeCloseCard)
{
	m_strTimeCloseCard = strTimeCloseCard;
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