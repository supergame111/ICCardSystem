#pragma once
class ISO14443A_MF
{
private:
	static HMODULE m_hDll;
	unsigned char m_cMode;
	unsigned char m_cBlockStartAddr;
	unsigned char m_cBlockNum;
	unsigned char m_cSectionAddr;
	CString m_strKey;
	CString m_strCardNo;
	unsigned char m_cErrorCode;
public:
	static BOOL CallExDll(void);
	static BOOL UncallExDll(void);
	static BOOL CStringToByteArr(const CString & strSrc, unsigned char * p_cDest, const int & nDestSize);
	static void ByteArrToCString(const BYTE * p_cSrc, const int & nSrcSize, CString & strDest);
	ISO14443A_MF();
	ISO14443A_MF(unsigned char cMode, unsigned char cBlockStartAddr, unsigned char cBlockNum, unsigned char cSectionAddr, const CString & strKey);
	virtual ~ISO14443A_MF();
	unsigned char GetMode() const;
	unsigned char GetBlockStartAddr() const;
	unsigned char GetBlockNum() const;
	unsigned char GetSectionAddr() const;
	CString GetKey() const;
	CString GetCardNo() const;
	unsigned char GetErrorCode() const;
	int ControlLED(const int & nFreq, const int & nDuration);
	int ControlBuzzer(const int & nFreq, const int & nDuration);
	int MF_Read(CString & strData);
	int MF_Write(const CString & strData);
	int MF_InitValue(const CString & strData);
	int MF_Dec(int & nValue);
	int MF_Inc(int & nValue);
	CString ErrorInfo(int nError);
	CString ErrorReason(unsigned char cErrorCode);
};

