#include "stdafx.h"
#include "CEmployeeDB.h"


CEmployeeDB::CEmployeeDB()
	: m_strPathDB(_T(""))
{
	m_strPathDB = ZUtil::GetExeCatalogPath() + _T("\\Data.mdb");
	CreateTable();
}


CEmployeeDB::~CEmployeeDB()
{
}


void CEmployeeDB::CreateTable()
{
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql;
	strSql = _T("CREATE TABLE Employee (\
				ID INT PRIMARY KEY NOT NULL,\
				Name NVARCHAR(100),\
				Password NVARCHAR(100),\
				GradeID INT,\
				IsUsing INT\
				)");
	zsql.ExecSQL(strSql);
}


bool CEmployeeDB::Insert(const CEmployee & employee)
{
	CreateTable();
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql, strError;
	strSql.Format(_T("INSERT INTO Employee VALUES (%d,'%s','%s',%d,%d)"), employee.GetID(), employee.GetName(), employee.GetPassword(),employee.GetGradeID(), employee.IsUsing());
	if (zsql.ExecSQL(strSql, &strError) == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}


bool CEmployeeDB::Update(const CEmployee & employee)
{
	CreateTable();
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql, strError;
	strSql.Format(_T("UPDATE Employee SET Name='%s',Password='%s',GradeID=%d,IsUsing=%d WHERE ID=%d"), employee.GetName(), employee.GetPassword(), employee.GetGradeID(), employee.IsUsing(), employee.GetID());
	if (zsql.ExecSQL(strSql, &strError) == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}


bool CEmployeeDB::Select(const CString & strSql, std::vector<CEmployee> & vec_employee)
{
	vec_employee.clear();
	std::vector<std::vector <CString>> vec2_strData;
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strError;
	int nRtn = zsql.GetTable(strSql, vec2_strData, &strError);
	int nRow = vec2_strData.size();
	if (nRow)
	{
		int nColumn = vec2_strData[0].size();
		if (nColumn == 5)
		{
			for (int i = 1; i < nRow; ++i)
			{
				CEmployee employee(_ttoi(vec2_strData[i][0]), vec2_strData[i][1], vec2_strData[i][2], _ttoi(vec2_strData[i][3]), _ttoi(vec2_strData[i][4]));
				vec_employee.push_back(employee);
			}
		}
	}
	if (nRtn == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}