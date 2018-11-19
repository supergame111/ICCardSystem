#pragma once
class CCardOperator
{
public:
	enum CARDTYPE
	{
		TYPE_SET = 0x1111,
		TYPE_RESET = 0x2222,
		TYPE_PRICE = 0x3333,
		TYPE_QUERY = 0x4444,
		TYPE_TEST = 0x5555,
		TYPE_USER = 0x8888
	};
public:
	CCardOperator();
	virtual ~CCardOperator();
	static bool ReadCard(CString & strCard, CString & strError, bool bIsCtrlReader = false);
	static bool WriteCard(const CString & strCard, CString & strError, bool bIsCtrlReader = false);
	static bool ClearUserCard(bool bIsCtrlReader = false);
	static void DecodeCard(const CString & strCard, int & nDeviceID, int  & nUnitID, int  & nCardType);
	static CString EncodeUserCard(int nDeviceID,int nUnitID,int nCardType,int nUserID,int nBalance);
	static void DecodeUserCard(const CString & strCard, int & nDeviceID, int  & nUnitID, int  & nCardType, int  & nUserID, int  & nBalance);
	static CString EncodeSetCard(int nDeviceID, int nUnitID, int nCardType, int  nPortNum, int nChargeTime, int nUnitPrice);
	static void DecodeSetCard(const CString & strCard, int & nDeviceID, int  & nUnitID, int  & nCardType, int  & nPortNum, int & nChargeTime,int & nUnitPrice);
	static CString EncodeResetCard(int nDeviceID, int nUnitID, int nCardType, int nWriteDeviceID);
	static void DecodeResetCard(const CString & strCard, int & nDeviceID, int  & nUnitID, int  & nCardType, int & nWriteDeviceID);
	static CString EncodePriceCard(int nDeviceID, int nUnitID, int nCardType, int nPrice);
	static void DecodePriceCard(const CString & strCard, int & nDeviceID, int  & nUnitID, int  & nCardType,int & nPrice);
	static CString EncodeQueryCard(int nDeviceID, int nUnitID, int nCardType);
	static void DecodeQueryCard(const CString & strCard, int & nDeviceID, int  & nUnitID, int  & nCardType);
	static CString EncodeTestCard(int nDeviceID, int nUnitID, int nCardType);
	static void DecodeTestCard(const CString & strCard, int & nDeviceID, int  & nUnitID, int  & nCardType);
};

