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
	if (!block_0A.MF_Read(strCard))
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
		ISO14443A_MF block_0B(0x00, 0x0B, 1, 0x02, _T("FFFFFFFFFFFF"));
		int nRtn_0B = block_0B.MF_Write(_T("53546364737408778F69010203070901"));
		if (!nRtn_0B)
		{
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
			}
		}
		else
		{
			strError = block_0B.ErrorInfo(nRtn_0B);
			if (nRtn_0B == 0x01)
			{
				strError += _T("\r\n") + block_0B.ErrorReason(block_0B.GetErrorCode());
			}
		}
	}
	if (bIsCtrlReader)
	{
		ISO14443A_MF ctrl;
		ctrl.ControlLED(0x16, 0);
	}
	return false;
}


bool CCardOperator::WriteCard(const CString & strCard, CString & strError, bool bIsCtrlReader)
{
	if (bIsCtrlReader)
	{
		ISO14443A_MF ctrl;
		ctrl.ControlLED(0x16, 10);
	}
	ISO14443A_MF block_0A;
	if (!block_0A.MF_Write(strCard))
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
		ISO14443A_MF block_0B(0x00, 0x0B, 1, 0x02, _T("FFFFFFFFFFFF"));
		int nRtn_0B = block_0B.MF_Write(_T("53546364737408778F69010203070901"));
		if (!nRtn_0B)
		{
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
			}
		}
		else
		{
			strError = block_0B.ErrorInfo(nRtn_0B);
			if (nRtn_0B == 0x01)
			{
				strError += _T("\r\n") + block_0B.ErrorReason(block_0B.GetErrorCode());
			}
		}
	}
	if (bIsCtrlReader)
	{
		ISO14443A_MF ctrl;
		ctrl.ControlLED(0x16, 0);
	}
	return false;
}


bool CCardOperator::ClearUserCard(bool bIsCtrlReader)
{
	if (bIsCtrlReader)
	{
		ISO14443A_MF ctrl;
		ctrl.ControlLED(0x16, 10);
	}
	ISO14443A_MF block_0A;
	if (block_0A.MF_Write(_T("00000000000000000000000000000000")))
	{
		if (bIsCtrlReader)
		{
			ISO14443A_MF ctrl;
			ctrl.ControlLED(0x16, 0);
		}
		return false;
	}
	else
	{
		if (bIsCtrlReader)
		{
			ISO14443A_MF ctrl;
			ctrl.ControlLED(0x16, 0);
			ctrl.ControlBuzzer(0x16, 1);
		}
		return true;
	}
}


void CCardOperator::DecodeCard(const CString & strCard, int & nDeviceID, int  & nUnitID, int  & nCardType)
{
	nDeviceID = _tcstol(strCard.Mid(0, 8), NULL, 16);
	nUnitID = _tcstol(strCard.Mid(8, 4), NULL, 16);
	nCardType = _tcstol(strCard.Mid(12, 4), NULL, 16);
}


CString CCardOperator::EncodeUserCard(int nDeviceID, int nUnitID, int nCardType, int nUserID, int nBalance)
{
	CString strCard;
	strCard.Format(_T("%08X%04X%04X%08X%08X"), nDeviceID, nUnitID, nCardType, nUserID, nBalance);
	return strCard;
}


void CCardOperator::DecodeUserCard(const CString & strCard, int & nDeviceID, int  & nUnitID, int  & nCardType, int  & nUserID, int  & nBalance)
{
	nDeviceID = _tcstol(strCard.Mid(0, 8), NULL, 16);
	nUnitID = _tcstol(strCard.Mid(8, 4), NULL, 16);
	nCardType = _tcstol(strCard.Mid(12, 4), NULL, 16);
	nUserID = _tcstol(strCard.Mid(16, 8), NULL, 16);
	nBalance = _tcstol(strCard.Mid(24, 8), NULL, 16);
}


CString CCardOperator::EncodeSetCard(int nDeviceID, int nUnitID, int nCardType, int  nPortNum, int nChargeTime, int nUnitPrice)
{
	CString strCard;
	strCard.Format(_T("%08X%04X%04X%04X%04X%08X"), nDeviceID, nUnitID, nCardType, nPortNum, nChargeTime, nUnitPrice);
	return strCard;
}


void CCardOperator::DecodeSetCard(const CString & strCard, int & nDeviceID, int  & nUnitID, int  & nCardType, int  & nPortNum, int & nChargeTime, int & nUnitPrice)
{
	nDeviceID = _tcstol(strCard.Mid(0, 8), NULL, 16);
	nUnitID = _tcstol(strCard.Mid(8, 4), NULL, 16);
	nCardType = _tcstol(strCard.Mid(12, 4), NULL, 16);
	nPortNum = _tcstol(strCard.Mid(16, 4), NULL, 16);
	nChargeTime = _tcstol(strCard.Mid(20, 4), NULL, 16);
	nUnitPrice = _tcstol(strCard.Mid(24, 8), NULL, 16);
}


CString CCardOperator::EncodeResetCard(int nDeviceID, int nUnitID, int nCardType,int nWriteDeviceID)
{
	CString strCard;
	strCard.Format(_T("%08X%04X%04X%08X%08X"), nDeviceID, nUnitID, nCardType, nWriteDeviceID, 0x55555555);
	return strCard;
}


void CCardOperator::DecodeResetCard(const CString & strCard, int & nDeviceID, int  & nUnitID, int  & nCardType, int & nWriteDeviceID)
{
	nDeviceID = _tcstol(strCard.Mid(0, 8), NULL, 16);
	nUnitID = _tcstol(strCard.Mid(8, 4), NULL, 16);
	nCardType = _tcstol(strCard.Mid(12, 4), NULL, 16);
	nWriteDeviceID = _tcstol(strCard.Mid(16, 8), NULL, 16);
}


CString CCardOperator::EncodePriceCard(int nDeviceID, int nUnitID, int nCardType,int nPrice)
{
	CString strCard;
	strCard.Format(_T("%08X%04X%04X%08X%08X"), nDeviceID, nUnitID, nCardType, 0x00000000, nPrice);
	return strCard;
}


void CCardOperator::DecodePriceCard(const CString & strCard, int & nDeviceID, int  & nUnitID, int  & nCardType, int & nPrice)
{
	nDeviceID = _tcstol(strCard.Mid(0, 8), NULL, 16);
	nUnitID = _tcstol(strCard.Mid(8, 4), NULL, 16);
	nCardType = _tcstol(strCard.Mid(12, 4), NULL, 16);
	nPrice = _tcstol(strCard.Mid(24, 8), NULL, 16);
}


CString CCardOperator::EncodeQueryCard(int nDeviceID, int nUnitID, int nCardType)
{
	CString strCard;
	strCard.Format(_T("%08X%04X%04X%08X%08X"), nDeviceID, nUnitID, nCardType, 0x66666666, 0x66666666);
	return strCard;
}


void CCardOperator::DecodeQueryCard(const CString & strCard, int & nDeviceID, int  & nUnitID, int  & nCardType)
{
	DecodeCard(strCard, nDeviceID, nUnitID, nCardType);
}


CString CCardOperator::EncodeTestCard(int nDeviceID, int nUnitID, int nCardType)
{
	CString strCard;
	strCard.Format(_T("%08X%04X%04X%08X%08X"), nDeviceID, nUnitID, nCardType, 0x66666666, 0x66666666);
	return strCard;
}


void CCardOperator::DecodeTestCard(const CString & strCard, int & nDeviceID, int  & nUnitID, int  & nCardType)
{
	DecodeCard(strCard, nDeviceID, nUnitID, nCardType);
}