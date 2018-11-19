#pragma once
#include "ZSqlite3.h"
class CUnionDB
{
private:
	CString m_strPathDB;
public:
	CUnionDB();
	virtual ~CUnionDB();
	bool Select(const CString & strSql, std::vector<std::vector<CString>> & vec2_strData);
};

