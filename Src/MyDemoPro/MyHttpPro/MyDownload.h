#pragma once

#include "afxinet.h"

class CMyDownload
{
public:
	void SetUrl(const CString& strURL);
	void SetDownloadPath(const CString& strPath);
	BOOL Download();
	const CString& GetFile() { return m_strFullFile; }

private:
	CString m_strUrl;
	CString m_strPath;
	CString m_strFullFile;
	BOOL m_bSuccess = FALSE;

private:
	// MFC Http class
	CInternetSession m_session;
	CHttpConnection* m_pHttpConnection = NULL;
	CHttpFile* m_pHttpFile = NULL;

	CString m_strServer;
	CString m_strObject;
	INTERNET_PORT m_wPort;
	DWORD m_dwType;

private:
	void OpenSession();
	void CloseSession();

	void OpenConnection();
	void CloseConnection();

	void OpenHttpFile();
	void CloseHttpFile();

	void ReadFile();
};



