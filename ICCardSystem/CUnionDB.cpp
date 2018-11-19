#include "stdafx.h"
#include "CUnionDB.h"


CUnionDB::CUnionDB()
	: m_strPathDB(_T(""))
{
	m_strPathDB = ZUtil::GetExeCatalogPath() + _T("\\Data.mdb");
}


CUnionDB::~CUnionDB()
{
}


bool CUnionDB::Select(const CString & strSql, std::vector<std::vector<CString>> & vec2_strData)
{
	vec2_strData.clear();
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strError;
	if (zsql.GetTable(strSql, vec2_strData, &strError) == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}