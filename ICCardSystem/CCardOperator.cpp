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
		strCardNo=strCard.Left(8);
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


void CCardOperator::DecodeCard(const CString & strCard, CString & strCardNo, int  & nLicense, int  & nCardType)
{
	strCardNo = strCard.Mid(0, 8);
	nLicense = _tcstol(strCard.Mid(8, 4), NULL, 16);
	nCardType = _tcstol(strCard.Mid(12, 4), NULL, 16);
}


CString CCardOperator::EncodeUserCard(CString strCardNo, int nLicense, int nCardType, int nUserID, int nBalance)
{
	CString strCard;
	strCard.Format(_T("%s%04X%04X%08X%08X"), strCardNo, nLicense, nCardType, nUserID, nBalance);
	return strCard;
}


void CCardOperator::DecodeUserCard(const CString & strCard, CString & strCardNo, int  & nLicense, int  & nCardType, int  & nUserID, int  & nBalance)
{
	strCardNo = strCard.Mid(0, 8);
	nLicense = _tcstol(strCard.Mid(8, 4), NULL, 16);
	nCardType = _tcstol(strCard.Mid(12, 4), NULL, 16);
	nUserID = _tcstol(strCard.Mid(16, 8), NULL, 16);
	nBalance = _tcstol(strCard.Mid(24, 8), NULL, 16);
}


CString CCardOperator::EncodeSetCard(CString strCardNo, int nLicense, int nCardType, int nRuptureCurrent, int  nPortNum, int nChargeTime, int nRatedCurrent, int nUnitPrice)
{
	CString strCard;
	strCard.Format(_T("%s%04X%04X%02X%02X%04X%04X%04X"), strCardNo, nLicense, nCardType, nRuptureCurrent, nPortNum, nChargeTime, nRatedCurrent, nUnitPrice);
	return strCard;
}


void CCardOperator::DecodeSetCard(const CString & strCard, CString & strCardNo, int  & nLicense, int  & nCardType, int & nRuptureCurrent, int  & nPortNum, int & nChargeTime, int & nRatedCurrent, int & nUnitPrice)
{
	strCardNo = strCard.Mid(0, 8);
	nLicense = _tcstol(strCard.Mid(8, 4), NULL, 16);
	nCardType = _tcstol(strCard.Mid(12, 4), NULL, 16);
	nRuptureCurrent = _tcstol(strCard.Mid(16, 2), NULL, 16);
	nPortNum = _tcstol(strCard.Mid(18, 2), NULL, 16);
	nChargeTime = _tcstol(strCard.Mid(20, 4), NULL, 16);
	nRatedCurrent = _tcstol(strCard.Mid(24, 4), NULL, 16);
	nUnitPrice = _tcstol(strCard.Mid(28, 4), NULL, 16);
}


CString CCardOperator::EncodeLicenseCard(CString strCardNo, int nLicense, int nCardType)
{
	CString strCard;
	strCard.Format(_T("%s%04X%04X%08X%08X"), strCardNo, nLicense, nCardType, 0x55555555, 0x55555555);
	return strCard;
}


void CCardOperator::DecodeLicenseCard(const CString & strCard, CString & strCardNo, int  & nLicense, int  & nCardType)
{
	strCardNo = strCard.Mid(0, 8);
	nLicense = _tcstol(strCard.Mid(8, 4), NULL, 16);
	nCardType = _tcstol(strCard.Mid(12, 4), NULL, 16);
}


CString CCardOperator::EncodeClearCard(CString strCardNo, int nLicense, int nCardType, int nUsageCount)
{
	CString strCard;
	strCard.Format(_T("%s%04X%04X%08X%08X"), strCardNo, nLicense, nCardType, nUsageCount, 0x66666666);
	return strCard;
}


void CCardOperator::DecodeClearCard(const CString & strCard, CString & strCardNo, int  & nLicense, int  & nCardType, int & nUsageCount)
{
	strCardNo = strCard.Mid(0, 8);
	nLicense = _tcstol(strCard.Mid(8, 4), NULL, 16);
	nCardType = _tcstol(strCard.Mid(12, 4), NULL, 16);
	nUsageCount = _tcstol(strCard.Mid(16, 8), NULL, 16);
}