#pragma once
#include "ZOperatorExcelFile.h"
#include <vector>
class ZExcelImport
{
public:
	class CCallBack
	{
	private:
		HANDLE m_hEvt;
		bool m_bIsRun;
	protected:
		CString m_strSrcPath;
		int m_nRowOffset;
		int m_nColumnOffset;
		std::vector<std::vector<CString>> m_vec2_strDataImport;
	public:
		CCallBack()
			: m_hEvt(NULL)
			, m_bIsRun(true)
			, m_strSrcPath(_T(""))
			, m_nRowOffset(0)
			, m_nColumnOffset(0)
		{
			if (!m_hEvt)
				m_hEvt = CreateEvent(NULL, TRUE, TRUE, NULL);
		};
		virtual ~CCallBack()
		{
			if (m_hEvt)
			{
				CloseHandle(m_hEvt);
				m_hEvt = NULL;
			}
		};
		virtual void OnImportProgressUpdate(int nProgress) = 0;
		virtual void OnImportResult(bool bResult) = 0;
		HANDLE GetEvt() { return m_hEvt; };
		bool IsRun() { return m_bIsRun; };
		CString GetSrcPath() { return m_strSrcPath; };
		int GetRowOffset() { return m_nRowOffset; };
		int GetColumnOffset() { return m_nColumnOffset; };
		std::vector<std::vector<CString>> & GetDataImport() { return m_vec2_strDataImport; };
		void StopRunImport()
		{
			m_bIsRun = false;
			WaitForSingleObject(m_hEvt, INFINITE);
		};
	};
private:
	CCallBack * m_p_callback;
	HANDLE m_hEvtCopyFinish;
	ZExcelImport(const ZExcelImport & ei);
	ZExcelImport & operator = (const ZExcelImport & ei);
	static UINT ImportThreadFunc(LPVOID lpParam);
public:
	ZExcelImport(CCallBack * p_callback);
	virtual ~ZExcelImport();
	bool Start();
};

