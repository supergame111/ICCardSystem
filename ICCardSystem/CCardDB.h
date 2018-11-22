#pragma once
#include "CCard.h"
#include "ZSqlite3.h"
class CCardDB
{
private:
	CString m_strPathDB;
	void CreateTable();
public:
	CCardDB();
	virtual ~CCardDB();
	bool Insert(const CCard & card);
	bool UpdateOpenCard(const CCard & card);
	bool UpdateCloseCard(const CCard & card);
	bool UpdateTotalAmount(const CCard & card);
	bool Select(const CString & strSql, std::vector<CCard> & vec_card);//strSql须为：SELECT *选择全部列才能返回对象
};

