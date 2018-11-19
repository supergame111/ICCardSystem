#pragma once
#include "CUser.h"
#include "ZSqlite3.h"
class CUserDB
{
private:
	CString m_strPathDB;
	void CreateTable();
public:
	CUserDB();
	virtual ~CUserDB();
	bool Insert(const CUser & user);
	bool UpdateModifyInfo(const CUser & user);
	bool UpdateOpenCard(const CUser & user);
	bool UpdateCloseCard(const CUser & user);
	bool UpdateTotalAmount(const CUser & user);
	bool Select(const CString & strSql , std::vector<CUser> & vec_user);//strSql须为：SELECT *选择全部列才能返回对象
};

