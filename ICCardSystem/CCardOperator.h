#pragma once
class CCardOperator
{
public:
	enum CARDTYPE
	{
		TYPE_SET = 0x1111,
		TYPE_LICENSE = 0x2222,
		TYPE_USER_TIME = 0x8800,
		TYPE_USER_RECHARGE = 0x8866
	};
public:
	CCardOperator();
	virtual ~CCardOperator();
	static bool ReadCard(CString & strCard, CString & strError, bool bIsCtrlReader = false);
	static bool ReadCardNo(CString & strCardNo, CString & strError, bool bIsCtrlReader = false);
	static bool WriteCard(const CString & strCard, CString & strError, bool bIsCtrlReader = false);
	static bool ClearUserCard(bool bIsCtrlReader = false);
	static void DecodeCard(const CString & strCard, CString & strCardNo, int  & nLicense, int  & nCardType);
	static CString EncodeUserCard(CString strCardNo,int nLicense,int nCardType,int nUserID,int nBalance);
	static void DecodeUserCard(const CString & strCard, CString & strCardNo, int  & nLicense, int  & nCardType, int  & nUserID, int  & nBalance);
	static CString EncodeSetCard(CString strCardNo, int nLicense, int nCardType, int  nPortNum, int nChargeTime, int nUnitPrice);
	static void DecodeSetCard(const CString & strCard, CString & strCardNo, int  & nLicense, int  & nCardType, int  & nPortNum, int & nChargeTime,int & nUnitPrice);
	static CString EncodeLicenseCard(CString strCardNo, int nLicense, int nCardType);
	static void DecodeLicenseCard(const CString & strCard, CString & strCardNo, int  & nLicense, int  & nCardType);
};

