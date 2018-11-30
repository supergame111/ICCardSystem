#include "stdafx.h"
#include "ZExcelImport.h"


ZExcelImport::ZExcelImport(CCallBack * p_callback)
	: m_p_callback(p_callback)
	, m_hEvtCopyFinish(NULL)
{
	if (!m_hEvtCopyFinish)
		m_hEvtCopyFinish = CreateEvent(NULL, TRUE, TRUE, NULL);
}


ZExcelImport::~ZExcelImport()
{
	WaitForSingleObject(m_hEvtCopyFinish, INFINITE);
	if (m_hEvtCopyFinish)
	{
		CloseHandle(m_hEvtCopyFinish);
		m_hEvtCopyFinish = NULL;
	}
}


bool ZExcelImport::Start()
{
	ResetEvent(m_hEvtCopyFinish);
	if (AfxBeginThread(ImportThreadFunc, (LPVOID)this))
	{
		return true;
	}
	SetEvent(m_hEvtCopyFinish);
	return false;
}


UINT ZExcelImport::ImportThreadFunc(LPVOID lpParam)
{
	ZExcelImport * p_ei = (ZExcelImport *)lpParam;
	CCallBack * p_callback = p_ei->m_p_callback;
	SetEvent(p_ei->m_hEvtCopyFinish);
	ResetEvent(p_callback->GetEvt());
	CString strError;
	bool bResult = false;
	ZOperatorExcelFile::InitOle();
	ZOperatorExcelFile operatorexcel;
	if (operatorexcel.InitExcel(&strError))
	{
		if (operatorexcel.OpenExcelFile(p_callback->GetSrcPath()))
		{
			if (operatorexcel.LoadSheet(0))
			{
				std::vector<std::vector<CString>> & vec2_Data = p_callback->GetDataImport();
				vec2_Data.clear();
				int nRow = (int)operatorexcel.GetRowCount();
				int nColumn = (int)operatorexcel.GetColumnCount();
				for (int i = p_callback->GetRowOffset(); i < nRow; ++i)
				{
					std::vector<CString> vec_strRow;
					for (int j = p_callback->GetColumnOffset(); j < nColumn; ++j)
						vec_strRow.push_back(operatorexcel.GetCellString((long)i, (long)j));
					vec2_Data.push_back(vec_strRow);
					int nProgress = 100;
					if (nRow > (p_callback->GetRowOffset()+1))
						nProgress = i * 100 / (nRow - p_callback->GetRowOffset()-1);
					if (p_callback->IsRun())
						p_callback->OnImportProgressUpdate(nProgress);
					else
						break;
				}
				bResult = true;
			}
			operatorexcel.CloseExcelFile();
		}
		operatorexcel.ReleaseExcel();
	}
	if (p_callback->IsRun())
		p_callback->OnImportResult(bResult);
	ZOperatorExcelFile::UninitOle();
	SetEvent(p_callback->GetEvt());
	return 0;
}
