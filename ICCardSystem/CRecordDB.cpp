#include "stdafx.h"
#include "CRecordDB.h"


CRecordDB::CRecordDB(const CString & strTableName)
	: m_strTableName(strTableName)
	, m_strPathDB(_T(""))
{
	m_strPathDB = ZUtil::GetExeCatalogPath() + _T("\\Data.mdb");
	CreateTable();
}


CRecordDB::~CRecordDB()
{
}


void CRecordDB::CreateTable()
{
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql;
	strSql.Format( _T("CREATE TABLE %s (\
				ID INT PRIMARY KEY NOT NULL,\
				UserID INT,\
				AmountOld INT,\
				Amount INT,\
				AmountNew INT,\
				Deposit INT,\
				Cost INT,\
				NoteInfo NVARCHAR(1000),\
				EmployeeID INT,\
				Time DATETIME\
				)"), m_strTableName);
	zsql.ExecSQL(strSql);
}


bool CRecordDB::Insert(const CRecord & record)
{
	CreateTable();
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strSql, strError;
	strSql.Format(_T("INSERT INTO %s VALUES (%d,%d,%d,%d,%d,%d,%d,'%s',%d,datetime('now','localtime'))"), m_strTableName, record.GetID(), record.GetUserID(), record.GetAmountOld(), record.GetAmount(), record.GetAmountNew(),record.GetDeposit(),record.GetCost(), record.GetNoteInfo(), record.GetEmployeeID());
	if (zsql.ExecSQL(strSql, &strError) == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}


bool CRecordDB::Select(const CString & strSql, std::vector<CRecord> & vec_record)
{
	vec_record.clear();
	std::vector<std::vector <CString>> vec2_strData;
	ZSqlite3 zsql;
	zsql.OpenDB(m_strPathDB);
	CString strError;
	int nRtn = zsql.GetTable(strSql, vec2_strData, &strError);
	int nRow = vec2_strData.size();
	if (nRow)
	{
		int nColumn = vec2_strData[0].size();
		if (nColumn == 10)
		{
			for (int i = 1; i < nRow; ++i)
			{
				CRecord record(_ttoi(vec2_strData[i][0]), _ttoi(vec2_strData[i][1]), _ttoi(vec2_strData[i][2]), _ttoi(vec2_strData[i][3]), _ttoi(vec2_strData[i][4]), _ttoi(vec2_strData[i][5]), _ttoi(vec2_strData[i][6]), vec2_strData[i][7], _ttoi(vec2_strData[i][8]), vec2_strData[i][9]);
				vec_record.push_back(record);
			}
		}
	}
	if (nRtn == ZSqlite3::ERROR_OK)
		return true;
	else
		return false;
}