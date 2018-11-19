#include "stdafx.h"
#include "CCardOperator.h"
#include "ISO14443A_MF.h"

CCardOperator::CCardOperator()
{
}


CCardOperator::~CCardOperator()
{
}


bool CCardOperator::ReadCard(CString & strCard, CString & strError, bool bIsCtrlReader)
{
	if (bIsCtrlReader)
	{
		ISO14443A_MF ctrl;
		ctrl.ControlLED(0x16, 10);
	}
	ISO14443A_MF block_0A;
	int nRtn_0A = block_0A.MF_Read(strCard);
	if (!nRtn_0A)
	{
		if (bIsCtrlReader)
		{
			ISO14443A_MF ctrl;
			ctrl.ControlLED(0x16, 0);
			ctrl.ControlBuzzer(0x16, 1);
		}
		return true;
	}
	else
	{
		strError = block_0A.ErrorInfo(nRtn_0A);
		if (nRtn_0A == 0x01)
		{
			strError += _T("\r\n") + block_0A.ErrorReason(block_0A.GetErrorCode());
		}
		if (bIsCtrlReader)
		{
			ISO14443A_MF ctrl;
			ctrl.ControlLED(0x16, 0);
		}
		return false;
	}
}


bool CCardOperator::ReadCardNo(CString & strCardNo, CString & strError, bool bIsCtrlReader)
{
	CString strCard;
	if (bIsCtrlReader)
	{
		ISO14443A_MF ctrl;
		ctrl.ControlLED(0x16, 10);
	}
	ISO14443A_MF block_00(0x00, 0x00, 1, 0x00, _T("FFFFFFFFFFFF"));
	int nRtn_0A = block_00.MF_Read(strCard);
	if (!nRtn_0A)
	{
		strCardNo.Format(_T("%d"), _tcstol(strCard.Left(8), NULL, 16));
		if (bIsCtrlReader)
		{
			ISO14443A_MF ctrl;
			ctrl.ControlLED(0x16, 0);
			ctrl.ControlBuzzer(0x16, 1);
		}
		return true;
	}
	else
	{
		strError = block_00.ErrorInfo(nRtn_0A);
		if (nRtn_0A == 0x01)
		{
			strError += _T("\r\n") + block_00.ErrorReason(block_00.GetErrorCode());
		}
		if (bIsCtrlReader)
		{
			ISO14443A_MF ctrl;
			ctrl.ControlLED(0x16, 0);
		}
		return false;
	}
}


bool CCardOperator::WriteCard(const CString & strCard, CString & strError, bool bIsCtrlReader)
{
	if (bIsCtrlReader)
	{
		ISO14443A_MF ctrl;
		ctrl.ControlLED(0x16, 10);
	}
	ISO14443A_MF block_0A;
	int nRtn_0A = block_0A.MF_Write(strCard);
	if (!nRtn_0A)
	{
		if (bIsCtrlReader)
		{
			ISO14443A_MF ctrl;
			ctrl.ControlLED(0x16, 0);
			ctrl.ControlBuzzer(0x16, 1);
		}
		return true;
	}
	else
	{
		strError = block_0A.ErrorInfo(nRtn_0A);
		if (nRtn_0A == 0x01)
		{
			strError += _T("\r\n") + block_0A.ErrorReason(block_0A.GetErrorCode());
		}
		if (bIsCtrlReader)
		{
			ISO14443A_MF ctrl;
			ctrl.ControlLED(0x16, 0);
		}
		return false;
	}
}


bool CCardOperator::ClearUserCard(bool bIsCtrlReader)
{
	if (bIsCtrlReader)
	{
		ISO14443A_MF ctrl;
		ctrl.ControlLED(0x16, 10);
	}
	ISO14443A_MF block_0A;
	int nRtn_0A = block_0A.MF_Write(_T("00000000000000000000000000000000"));
	if (!nRtn_0A)
	{
		if (bIsCtrlReader)
		{
			ISO14443A_MF ctrl;
			ctrl.ControlLED(0x16, 0);
			ctrl.ControlBuzzer(0x16, 1);
		}
		return true;
	}
	else
	{
		if (bIsCtrlReader)
		{
			ISO14443A_MF ctrl;
			ctrl.ControlLED(0x16, 0);
		}
		return false;
	}
}


void CCardOperator::DecodeCard(const CString & strCard, int & nCardNo, int  & nLicense, int  & nCardType)
{
	nCardNo = _tcstol(strCard.Mid(0, 8), NULL, 16);
	nLicense = _tcstol(strCard.Mid(8, 4), NULL, 16);
	nCardType = _tcstol(strCard.Mid(12, 4), NULL, 16);
}


CString CCardOperator::EncodeUserCard(int nCardNo, int nLicense, int nCardType, int nUserID, int nBalance)
{
	CString strCard;
	strCard.Format(_T("%08X%04X%04X%08X%08X"), nCardNo, nLicense, nCardType, nUserID, nBalance);
	return strCard;
}


void CCardOperator::DecodeUserCard(const CString & strCard, int & nCardNo, int  & nLicense, int  & nCardType, int  & nUserID, int  & nBalance)
{
	nCardNo = _tcstol(strCard.Mid(0, 8), NULL, 16);
	nLicense = _tcstol(strCard.Mid(8, 4), NULL, 16);
	nCardType = _tcstol(strCard.Mid(12, 4), NULL, 16);
	nUserID = _tcstol(strCard.Mid(16, 8), NULL, 16);
	nBalance = _tcstol(strCard.Mid(24, 8), NULL, 16);
}


CString CCardOperator::EncodeSetCard(int nCardNo, int nLicense, int nCardType, int  nPortNum, int nChargeTime, int nUnitPrice)
{
	CString strCard;
	strCard.Format(_T("%08X%04X%04X%04X%04X%08X"), nCardNo, nLicense, nCardType, nPortNum, nChargeTime, nUnitPrice);
	return strCard;
}


void CCardOperator::DecodeSetCard(const CString & strCard, int & nCardNo, int  & nLicense, int  & nCardType, int  & nPortNum, int & nChargeTime, int & nUnitPrice)
{
	nCardNo = _tcstol(strCard.Mid(0, 8), NULL, 16);
	nLicense = _tcstol(strCard.Mid(8, 4), NULL, 16);
	nCardType = _tcstol(strCard.Mid(12, 4), NULL, 16);
	nPortNum = _tcstol(strCard.Mid(16, 4), NULL, 16);
	nChargeTime = _tcstol(strCard.Mid(20, 4), NULL, 16);
	nUnitPrice = _tcstol(strCard.Mid(24, 8), NULL, 16);
}


CString CCardOperator::EncodeLicenseCard(int nCardNo, int nLicense, int nCardType)
{
	CString strCard;
	strCard.Format(_T("%08X%04X%04X%08X%08X"), nCardNo, nLicense, nCardType, 0x55555555, 0x55555555);
	return strCard;
}


void CCardOperator::DecodeLicenseCard(const CString & strCard, int & nCardNo, int  & nLicense, int  & nCardType)
{
	nCardNo = _tcstol(strCard.Mid(0, 8), NULL, 16);
	nLicense = _tcstol(strCard.Mid(8, 4), NULL, 16);
	nCardType = _tcstol(strCard.Mid(12, 4), NULL, 16);
}