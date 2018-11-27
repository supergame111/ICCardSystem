#include "stdafx.h"
#include "CCardDB.h"


CCardDB::CCardDB()
	: m_strPathDB(_T(""))
{
	m_strPathDB = ZUtil::GetExeCatalogPath() + _T("\\Data.mdb");
	CreateTable();
}


CCardDB::~CCardDB()
{
}


void CCardDB::CreateTable()
{
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql;
	strSql = _T("CREATE TABLE Card (\
				ID INT PRIMARY KEY NOT NULL,\
                UserID INT,\
                No NVARCHAR(100),\
                Type INT,\
                Deadline DATETIME,\
				Deposit INT DEFAULT 0,\
                TotalAmount INT DEFAULT 0,\
                State INT DEFAULT 0,\
				EmployeeIDOpenCard INT,\
				TimeOpenCard DATETIME,\
				EmployeeIDCloseCard INT,\
				TimeCloseCard DATETIME\
				)");
	zsql.ExecSQL(strSql);
}


bool CCardDB::Insert(const CCard & card)
{
	CreateTable();
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql, strError;
	strSql.Format(_T("INSERT INTO Card VALUES (%d,%d,'%s',%d,'%s',%d,%d,%d,%d,datetime('now','localtime'),NULL,NULL)"), card.GetID(),card.GetUserID(),card.GetNo(),card.GetType(),card.GetDeadline(),card.GetDeposit(), card.GetTotalAmount(),card.GetState(),card.GetEmployeeIDOpenCard());
	if (zsql.ExecSQL(strSql, &strError) == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}


bool CCardDB::UpdateOpenCard(const CCard & card)
{
	CreateTable();
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql, strError;
	strSql.Format(_T("UPDATE Card SET Type=%d,Deadline='%s',Deposit=%d,State=%d,EmployeeIDOpenCard=%d,TimeOpenCard=datetime('now','localtime'),EmployeeIDCloseCard=NULL,TimeCloseCard=NULL WHERE ID=%d"), card.GetType(),card.GetDeadline(),card.GetDeposit(),card.GetState(),card.GetEmployeeIDOpenCard(), card.GetID());
	if (zsql.ExecSQL(strSql, &strError) == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}


bool CCardDB::UpdateCloseCard(const CCard & card)
{
	CreateTable();
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql, strError;
	strSql.Format(_T("UPDATE Card SET State=%d,EmployeeIDCloseCard=%d,TimeCloseCard=datetime('now','localtime') WHERE ID=%d"), card.GetState(),card.GetEmployeeIDCloseCard(), card.GetID());
	if (zsql.ExecSQL(strSql, &strError) == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}


bool CCardDB::UpdateTotalAmount(const CCard & card)
{
	CreateTable();
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql, strError;
	strSql.Format(_T("UPDATE Card SET TotalAmount=%d WHERE ID=%d"), card.GetTotalAmount(), card.GetID());
	if (zsql.ExecSQL(strSql, &strError) == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}


bool CCardDB::Select(const CString & strSql, std::vector<CCard> & vec_card)
{
	vec_card.clear();
	std::vector<std::vector <CString>> vec2_strData;
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strError;
	int nRtn = zsql.GetTable(strSql, vec2_strData, &strError);
	int nRow = vec2_strData.size();
	if (nRow)
	{
		int nColumn = vec2_strData[0].size();
		if (nColumn == 12)
		{
			for (int i = 1; i < nRow; ++i)
			{
				CCard card(_ttoi(vec2_strData[i][0]), _ttoi(vec2_strData[i][1]), vec2_strData[i][2], _ttoi(vec2_strData[i][3]), vec2_strData[i][4], _ttoi(vec2_strData[i][5]), _ttoi(vec2_strData[i][6]), _ttoi(vec2_strData[i][7]), _ttoi(vec2_strData[i][8]), vec2_strData[i][9], _ttoi(vec2_strData[i][10]), vec2_strData[i][11]);
				vec_card.push_back(card);
			}
		}
	}
	if (nRtn == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}