#include "stdafx.h"
#include "CUserDB.h"


CUserDB::CUserDB()
	: m_strPathDB(_T(""))
{
	m_strPathDB = ZUtil::GetExeCatalogPath() + _T("\\Data.mdb");
	CreateTable();
}


CUserDB::~CUserDB()
{
}


void CUserDB::CreateTable()
{
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql;
	strSql = _T("CREATE TABLE User (\
				ID INT PRIMARY KEY NOT NULL,\
				Name NVARCHAR(100),\
				IDNo NVARCHAR(100),\
				PhoneNo NVARCHAR(100),\
				Addr NVARCHAR(100),\
				License INT,\
				TotalAmount INT DEFAULT 0,\
				State INT DEFAULT 0,\
				NoteInfo NVARCHAR(1000),\
				EmployeeIDAdd INT,\
				TimeAdd DATETIME,\
				EmployeeIDLastModify INT,\
				TimeLastModify DATETIME\
				)");
	zsql.ExecSQL(strSql);
}

bool CUserDB::Insert(const CUser & user)
{
	CreateTable();
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql, strError;
	strSql.Format(_T("INSERT INTO User VALUES (%d,'%s','%s','%s','%s',%d,%d,%d,'%s',%d,datetime('now','localtime'),%d,datetime('now','localtime'))"),user.GetID(), user.GetName(), user.GetIDNo(), user.GetPhoneNo(), user.GetAddr(), user.GetLicense(), user.GetTotalAmount(),user.GetState(),user.GetNoteInfo(), user.GetEmployeeIDAdd(), user.GetEmployeeIDLastModify());
	if (zsql.ExecSQL(strSql, &strError) == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}


bool CUserDB::UpdateModifyInfo(const CUser & user)
{
	CreateTable();
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql, strError;
	strSql.Format(_T("UPDATE User SET Name='%s',IDNo='%s',PhoneNo='%s',Addr='%s',NoteInfo='%s',EmployeeIDLastModify=%d,TimeLastModify=datetime('now','localtime') WHERE ID=%d"), user.GetName(), user.GetIDNo(), user.GetPhoneNo(), user.GetAddr(), user.GetNoteInfo(), user.GetEmployeeIDLastModify(), user.GetID());
	if (zsql.ExecSQL(strSql, &strError) == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}


bool CUserDB::UpdateOpenCard(const CUser & user)
{
	CreateTable();
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql, strError;
	strSql.Format(_T("UPDATE User SET License=%d,State=%d WHERE ID=%d"), user.GetLicense(), user.GetState(), user.GetID());
	if (zsql.ExecSQL(strSql, &strError) == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}


bool CUserDB::UpdateCloseCard(const CUser & user)
{
	CreateTable();
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql, strError;
	strSql.Format(_T("UPDATE User SET State=%d WHERE ID=%d"), user.GetState(), user.GetID());
	if (zsql.ExecSQL(strSql, &strError) == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}


bool CUserDB::UpdateTotalAmount(const CUser & user)
{
	CreateTable();
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql, strError;
	strSql.Format(_T("UPDATE User SET TotalAmount=%d WHERE ID=%d"), user.GetTotalAmount(), user.GetID());
	if (zsql.ExecSQL(strSql, &strError) == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}


bool CUserDB::Select(const CString & strSql , std::vector<CUser> & vec_user)
{
	vec_user.clear();
	std::vector<std::vector <CString>> vec2_strData;
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strError;
	int nRtn = zsql.GetTable(strSql, vec2_strData, &strError);
	int nRow = vec2_strData.size();
	if (nRow)
	{
		int nColumn = vec2_strData[0].size();
		if (nColumn == 13)
		{
			for (int i = 1; i < nRow; ++i)
			{
				CUser user(_ttoi(vec2_strData[i][0]), vec2_strData[i][1], vec2_strData[i][2], vec2_strData[i][3], vec2_strData[i][4], _ttoi(vec2_strData[i][5]), _ttoi(vec2_strData[i][6]), _ttoi(vec2_strData[i][7]), vec2_strData[i][8], _ttoi(vec2_strData[i][9]), vec2_strData[i][10], _ttoi(vec2_strData[i][11]), vec2_strData[i][12]);
				vec_user.push_back(user);
			}
		}
	}
	if (nRtn == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}