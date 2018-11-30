#pragma once
#include "ZOperatorExcelFile.h"
#include <vector>
class ZExcelExport
{
public:
	class CCallBack
	{
	private:
		HANDLE m_hEvt;
		bool m_bIsRun;
	protected:
		CString m_strDestPath;
		CString m_strDemoPath;
		int m_nRowOffset;
		int m_nColumnOffset;
		std::vector<std::vector<CString>> m_vec2_strDataExport;
	public:
		CCallBack()
			: m_hEvt(NULL)
			, m_bIsRun(true)
			, m_strDestPath(_T(""))
			, m_strDemoPath(_T(""))
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
		virtual void OnExportProgressUpdate(int nProgress) = 0;
		virtual void OnExportResult(bool bResult) = 0;
		HANDLE GetEvt() { return m_hEvt; };
		bool IsRun() { return m_bIsRun; };
		CString GetDestPath() { return m_strDestPath; };
		CString GetDemoPath() { return m_strDemoPath; };
		int GetRowOffset() { return m_nRowOffset; };
		int GetColumnOffset() { return m_nColumnOffset; };
		const std::vector<std::vector<CString>> & GetDataExport() { return m_vec2_strDataExport; };
		void StopRunExport()
		{
			m_bIsRun = false;
			WaitForSingleObject(m_hEvt, INFINITE);
		};
	};
private:
	CCallBack * m_p_callback;
	HANDLE m_hEvtCopyFinish;
	ZExcelExport(const ZExcelExport & ee);
	ZExcelExport & operator = (const ZExcelExport & ee);
	static UINT ExportThreadFunc(LPVOID lpParam);
public:
	ZExcelExport(CCallBack * p_callback);
	virtual ~ZExcelExport();
	bool Start();
};

