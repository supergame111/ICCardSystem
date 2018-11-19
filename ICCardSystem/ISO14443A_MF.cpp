#include "stdafx.h"
#include "ISO14443A_MF.h"

HMODULE ISO14443A_MF::m_hDll = NULL;
const TCHAR tcSplitError = _T('_');

ISO14443A_MF::ISO14443A_MF()
	: m_cMode(0x02)
	, m_cBlockStartAddr(0x0A)
	, m_cBlockNum(1)
	, m_cSectionAddr(0x02)
	, m_strKey(_T("010203070901"))
	, m_strCardNo(_T(""))
	, m_cErrorCode(0)
{
}


ISO14443A_MF::ISO14443A_MF(unsigned char cMode, unsigned char cBlockStartAddr, unsigned char cBlockNum, unsigned char cSectionAddr,const CString & strKey)
	: m_cMode(cMode)
	, m_cBlockStartAddr(cBlockStartAddr)
	, m_cBlockNum(cBlockNum)
	, m_cSectionAddr(cSectionAddr)
	, m_strKey(strKey)
	, m_strCardNo(_T(""))
	, m_cErrorCode(0)
{
}


ISO14443A_MF::~ISO14443A_MF()
{
}


unsigned char ISO14443A_MF::GetMode() const
{
	return m_cMode;
}


unsigned char ISO14443A_MF::GetBlockStartAddr() const
{
	return m_cBlockStartAddr;
}


unsigned char ISO14443A_MF::GetBlockNum() const
{
	return m_cBlockNum;
}


unsigned char ISO14443A_MF::GetSectionAddr() const
{
	return m_cSectionAddr;
}


CString ISO14443A_MF::GetKey() const
{
	return m_strKey;
}


CString ISO14443A_MF::GetCardNo() const
{
	return m_strCardNo;
}


unsigned char ISO14443A_MF::GetErrorCode() const
{
	return m_cErrorCode;
}


BOOL ISO14443A_MF::CallExDll(void)
{
	m_hDll = LoadLibraryEx(_T("function.dll"), NULL, 0);
	if (!m_hDll)
		return FALSE;
	return TRUE;
}


BOOL ISO14443A_MF::UncallExDll(void)
{
	if (m_hDll)
		return FreeLibrary(m_hDll);
	return FALSE;
}


BOOL ISO14443A_MF::CStringToByteArr(const CString & strSrc, unsigned char * p_cDest, const int & nDestSize)
{
	CString strByte;
	int i = 0, j = 0, nLen;
	nLen = strSrc.GetLength() / 2;
	if (nLen > nDestSize)
		return FALSE;
	for (; i < nLen; ++i, j = j + 2)
	{
		strByte = strSrc.Mid(j, 2);
		p_cDest[i] = unsigned char(_tcstol(strByte, NULL, 16));
	}
	return TRUE;
}


void ISO14443A_MF::ByteArrToCString(const BYTE * p_cSrc, const int & nSrcSize, CString & strDest)
{
	strDest.Empty();
	CString strByte;
	for (int i = 0; i < nSrcSize; ++i)
	{
		strByte.Format(_T("%02X"), p_cSrc[i]);
		strDest += strByte;
	}
}


int ISO14443A_MF::ControlLED(const int & nFreq, const int & nDuration)
{
	typedef int(_stdcall * ControlLED)(unsigned char freq, unsigned char duration, unsigned char * buffer);
	ControlLED ctrlled;
	int nRtn = -1;
	ctrlled = (ControlLED)GetProcAddress(m_hDll, "ControlLED");
	if (ctrlled)
	{
		unsigned char sz_cBuffer[1024] = { 0 };
		nRtn = ctrlled(nFreq, nDuration, sz_cBuffer);
		if (nRtn)
			m_cErrorCode = sz_cBuffer[0];
	}
	return nRtn;
}


int ISO14443A_MF::ControlBuzzer(const int & nFreq, const int & nDuration)
{
	typedef int(_stdcall * ControlBuzzer)(unsigned char freq, unsigned char duration, unsigned char * buffer);
	ControlBuzzer ctrlbuzzer;
	int nRtn = -1;
	ctrlbuzzer = (ControlBuzzer)GetProcAddress(m_hDll, "ControlBuzzer");
	if (ctrlbuzzer)
	{
		unsigned char sz_cBuffer[1024] = { 0 };
		nRtn = ctrlbuzzer(nFreq, nDuration, sz_cBuffer);
		if (nRtn)
			m_cErrorCode = sz_cBuffer[0];
	}
	return nRtn;
}


int ISO14443A_MF::MF_Read(CString & strData)
{
	typedef int(_stdcall * MF_Read)(unsigned char mode, unsigned char blk_add, unsigned char num_blk, unsigned char * snr, unsigned char * buffer);
	MF_Read mfread;
	int nRtn = -1;
	mfread = (MF_Read)GetProcAddress(m_hDll, "MF_Read");
	if (mfread)
	{
		unsigned char sz_cSnr[6] = { 0 }, sz_cBuffer[1024] = { 0 };
		CStringToByteArr(m_strKey, sz_cSnr, sizeof(sz_cSnr));
		nRtn = mfread(m_cMode, m_cBlockStartAddr, m_cBlockNum, sz_cSnr, sz_cBuffer);
		if (!nRtn)
		{
			ByteArrToCString(sz_cSnr, 4, m_strCardNo);
			ByteArrToCString(sz_cBuffer, m_cBlockNum*16, strData);
		}
		else
			m_cErrorCode = sz_cBuffer[0];
	}
	return nRtn;
}


int ISO14443A_MF::MF_Write(const CString & strData)
{
	typedef int(_stdcall * MF_Write)(unsigned char mode, unsigned char blk_add, unsigned char num_blk, unsigned char * snr, unsigned char * buffer);
	MF_Write mfwrite;
	int nRtn = -1;
	mfwrite = (MF_Write)GetProcAddress(m_hDll, "MF_Write");
	if (mfwrite)
	{
		unsigned char sz_cSnr[6] = { 0 }, sz_cBuffer[1024] = { 0 };
		CStringToByteArr(m_strKey, sz_cSnr, sizeof(sz_cSnr));
		CStringToByteArr(strData, sz_cBuffer, sizeof(sz_cBuffer));
		nRtn = mfwrite(m_cMode, m_cBlockStartAddr, m_cBlockNum, sz_cSnr, sz_cBuffer);
		if (!nRtn)
		{
			ByteArrToCString(sz_cSnr, 4, m_strCardNo);
		}
		else
			m_cErrorCode = sz_cBuffer[0];
	}
	return nRtn;
}


int ISO14443A_MF::MF_InitValue(const CString & strData)
{
	typedef int(_stdcall * MF_InitValue)(unsigned char mode, unsigned char sectnum, unsigned char * snr, unsigned char * value);
	MF_InitValue mfinit;
	int nRtn = -1;
	mfinit = (MF_InitValue)GetProcAddress(m_hDll, "MF_InitValue");
	if (mfinit)
	{
		unsigned char sz_cSnr[6] = { 0 }, sz_cBuffer[4] = { 0 };
		CStringToByteArr(m_strKey, sz_cSnr, sizeof(sz_cSnr));
		CStringToByteArr(strData, sz_cBuffer, sizeof(sz_cBuffer));
		nRtn = mfinit(m_cMode, m_cSectionAddr, sz_cSnr, sz_cBuffer);
		if (!nRtn)
		{
			ByteArrToCString(sz_cSnr, 4, m_strCardNo);
		}
		else
			m_cErrorCode = sz_cSnr[0];
	}
	return nRtn;
}


int ISO14443A_MF::MF_Dec(int & nValue)
{
	typedef int(_stdcall * MF_Dec)(unsigned char mode, unsigned char sectnum, unsigned char * snr, int * value);
	MF_Dec mfdec;
	int nRtn = -1;
	mfdec = (MF_Dec)GetProcAddress(m_hDll, "MF_Dec");
	if (mfdec)
	{
		unsigned char sz_cSnr[6] = { 0 };
		CStringToByteArr(m_strKey, sz_cSnr, sizeof(sz_cSnr));
		nRtn = mfdec(m_cMode, m_cSectionAddr, sz_cSnr, &nValue);
		if (!nRtn)
		{
			ByteArrToCString(sz_cSnr, 4, m_strCardNo);
		}
		else
			m_cErrorCode = sz_cSnr[0];
	}
	return nRtn;
}


int ISO14443A_MF::MF_Inc(int & nValue)
{
	typedef int(_stdcall * MF_Inc)(unsigned char mode, unsigned char sectnum, unsigned char * snr, int * value);
	MF_Inc mfinc;
	int nRtn = -1;
	mfinc = (MF_Inc)GetProcAddress(m_hDll, "MF_Inc");
	if (mfinc)
	{
		unsigned char sz_cSnr[6] = { 0 };
		CStringToByteArr(m_strKey, sz_cSnr, sizeof(sz_cSnr));
		nRtn = mfinc(m_cMode, m_cSectionAddr, sz_cSnr, &nValue);
		if (!nRtn)
		{
			ByteArrToCString(sz_cSnr, 4, m_strCardNo);
		}
		else
			m_cErrorCode = sz_cSnr[0];
	}
	return nRtn;
}


CString ISO14443A_MF::ErrorInfo(int nError)
{
	CString strErrorInfo;
	strErrorInfo.Format(_T("0x%02X%c"), nError, tcSplitError);
	switch (nError)
	{
	case -1: strErrorInfo += _T("DLL调用出错"); break;
	case 0x00: strErrorInfo += _T("命令执行成功"); break;
	case 0x01: strErrorInfo += _T("命令操作失败"); break;
	case 0x02: strErrorInfo += _T("地址校验错误"); break;
	case 0x04: strErrorInfo += _T("读写器返回超时"); break;
	case 0x05: strErrorInfo += _T("数据包流水号不正确"); break;
	case 0x07: strErrorInfo += _T("接收异常"); break;
	case 0x0A: strErrorInfo += _T("参数值超出范围"); break;
	}
	return strErrorInfo;
}


CString ISO14443A_MF::ErrorReason(unsigned char cErrorCode)
{
	CString strErrorReason;
	strErrorReason.Format(_T("0x%02X%c"), cErrorCode, tcSplitError);
	switch (cErrorCode)
	{
	case 0x80: strErrorReason += _T("参数设置成功"); break;
	case 0x81: strErrorReason += _T("参数设置失败"); break;
	case 0x82: strErrorReason += _T("通讯超时"); break;
	case 0x83: strErrorReason += _T("卡不存在"); break;
	case 0x84: strErrorReason += _T("接收卡数据出错"); break;
	case 0x85: strErrorReason += _T("输入参数或者输入命令格式错误"); break;
	case 0x87: strErrorReason += _T("未知的错误"); break;
	case 0x8A: strErrorReason += _T("在对于卡块初始化命令中出现错误（仅用于14443命令）"); break;
	case 0x8B: strErrorReason += _T("在防冲突过程中得到错误的序列号（仅用于14443命令）"); break;
	case 0x8C: strErrorReason += _T("密码认证没通过（仅用于14443命令）"); break;
	case 0x8F: strErrorReason += _T("输入的指令代码不存在"); break;
	case 0x90: strErrorReason += _T("卡不支持这个命令（仅用于15693命令）"); break;
	case 0x91: strErrorReason += _T("命令格式有错误（仅用于15693命令）"); break;
	case 0x92: strErrorReason += _T("在命令的FLAG参数中，不支持OPTION 模式（仅用于15693命令）"); break;
	case 0x93: strErrorReason += _T("要操作的BLOCK不存在（仅用于15693命令）"); break;
	case 0x94: strErrorReason += _T("要操作的对象已经别锁定，不能进行修改（仅用于15693命令）"); break;
	case 0x95: strErrorReason += _T("锁定操作不成功（仅用于15693命令）"); break;
	case 0x96: strErrorReason += _T("写操作不成功（仅用于15693命令）"); break;
	}
	return strErrorReason;
}