#include "stdafx.h"
#include "CCard.h"


CCard::CCard()
{
}


CCard::CCard(int nID, int nUserID, int nNo,int nType, CString strDeadline, int nDeposit, int nEmployeeIDOpenCard, CString strTimeOpenCard, int nEmployeeIDCloseCard, CString strTimeCloseCard)
	: m_nID(nID)
	, m_nUserID(nUserID)
	, m_nNo(nNo)
	, m_nType(nType)
	, m_strDeadline(strDeadline)
	, m_nDeposit(nDeposit)
	, m_nEmployeeIDOpenCard(nEmployeeIDOpenCard)
	, m_strTimeOpenCard(strTimeOpenCard)
	, m_nEmployeeIDCloseCard(nEmployeeIDCloseCard)
	, m_strTimeCloseCard(strTimeCloseCard)
{
}


CCard::~CCard()
{
}


int CCard::GetID() const
{
	return m_nID;
}


int CCard::GetUserID() const
{
	return m_nUserID;
}


int CCard::GetNo() const
{
	return m_nNo;
}


int CCard::GetType() const
{
	return m_nType;
}


CString CCard::GetDeadline() const
{
	return m_strDeadline;
}


int CCard::GetDeposit() const
{
	return m_nDeposit;
}


int CCard::GetEmployeeIDOpenCard() const
{
	return m_nEmployeeIDOpenCard;
}


CString CCard::GetTimeOpenCard() const
{
	return m_strTimeOpenCard;
}


int CCard::GetEmployeeIDCloseCard() const
{
	return m_nEmployeeIDCloseCard;
}


CString CCard::GetTimeCloseCard() const
{
	return m_strTimeCloseCard;
}