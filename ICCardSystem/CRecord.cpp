#include "stdafx.h"
#include "CRecord.h"


CRecord::CRecord()
{
}


CRecord::CRecord(int nID, int nUserID, CString strCardNo, int nAmountOld, int nAmount, int nAmountNew, int nDeposit, CString strNoteInfo, int nEmployeeID, CString strTime)
	: m_nID(nID)
	, m_nUserID(nUserID)
	, m_strCardNo(strCardNo)
	, m_nAmountOld(nAmountOld)
	, m_nAmount(nAmount)
	, m_nAmountNew(nAmountNew)
	, m_nDeposit(nDeposit)
	, m_strNoteInfo(strNoteInfo)
	, m_nEmployeeID(nEmployeeID)
	, m_strTime(strTime)
{
}


CRecord::~CRecord()
{
}


int CRecord::GetID() const
{
	return m_nID;
}


int CRecord::GetUserID() const
{
	return m_nUserID;
}


CString CRecord::GetCardNo() const
{
	return m_strCardNo;
}


int CRecord::GetAmountOld() const
{
	return m_nAmountOld;
}


int CRecord::GetAmount() const
{
	return m_nAmount;
}


int CRecord::GetAmountNew() const
{
	return m_nAmountNew;
}


int CRecord::GetDeposit() const
{
	return m_nDeposit;
}


CString CRecord::GetNoteInfo() const
{
	return m_strNoteInfo;
}


int CRecord::GetEmployeeID() const
{
	return m_nEmployeeID;
}


CString CRecord::GetTime() const
{
	return m_strTime;
}