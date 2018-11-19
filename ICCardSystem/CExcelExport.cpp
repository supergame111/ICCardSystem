#include "stdafx.h"
#include "CExcelExport.h"


CExcelExport::CExcelExport()
	: m_p_callback(NULL)
	, m_hEvtCopyFinish(NULL)
{
	if (!m_hEvtCopyFinish)
		m_hEvtCopyFinish = CreateEvent(NULL, TRUE, TRUE, NULL);
}


CExcelExport::CExcelExport(CCallBack * p_callback)
	: m_p_callback(p_callback)
	, m_hEvtCopyFinish(NULL)
{
	if (!m_hEvtCopyFinish)
		m_hEvtCopyFinish = CreateEvent(NULL, TRUE, TRUE, NULL);
}


CExcelExport::~CExcelExport()
{
	WaitForSingleObject(m_hEvtCopyFinish, INFINITE);
	if (m_hEvtCopyFinish)
	{
		CloseHandle(m_hEvtCopyFinish);
		m_hEvtCopyFinish = NULL;
	}
}


bool CExcelExport::Start()
{
	ResetEvent(m_hEvtCopyFinish);
	if (AfxBeginThread(ExportThreadFunc, (LPVOID)this))
	{
		return true;
	}
	SetEvent(m_hEvtCopyFinish);
	return false;
}


UINT CExcelExport::ExportThreadFunc(LPVOID lpParam)
{
	CExcelExport * p_ee = (CExcelExport *)lpParam;
	CCallBack * p_callback = p_ee->m_p_callback;
	SetEvent(p_ee->m_hEvtCopyFinish);
	ResetEvent(p_callback->GetEvt());
	CString strError;
	bool bResult = false;
	ZOperatorExcelFile::InitOle();
	ZOperatorExcelFile operatorexcel;
	if (operatorexcel.InitExcel(&strError))
	{
		if (operatorexcel.OpenExcelFile(p_callback->GetDemoPath()))
		{
			if (operatorexcel.LoadSheet(0))
			{
				const std::vector<std::vector<CString>> & vec2_Data = p_callback->GetData();
				int nRow = vec2_Data.size();
				if (nRow)
				{
					int nColumn = vec2_Data[0].size();
					for (int i = 0; i < nRow; ++i)
					{
						for (int j = 0; j < nColumn; ++j)
							operatorexcel.SetCellString(i + p_callback->GetRowOffset(), j + p_callback->GetColumnOffset(), vec2_Data[i][j]);
						int nProgress = 100;
						if (nRow > 1)
							nProgress = i * 100 / (nRow - 1);
						if (p_callback->IsRun())
							p_callback->OnExportProgressUpdate(nProgress);
						else
							break;
					}
				}
				operatorexcel.SaveasXSLFile(p_callback->GetDestPath());
				bResult = true;
			}
			operatorexcel.CloseExcelFile();
		}
		operatorexcel.ReleaseExcel();
	}
	if(p_callback->IsRun())
		p_callback->OnExportResult(bResult);
	ZOperatorExcelFile::UninitOle();
	SetEvent(p_callback->GetEvt());
	return 0;
}