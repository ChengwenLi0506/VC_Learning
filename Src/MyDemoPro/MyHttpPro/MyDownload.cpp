
#include "pch.h"
#include "MyDownload.h"



void CMyDownload::SetUrl(const CString& strURL)
{
	m_strUrl = strURL;
}

void CMyDownload::SetDownloadPath(const CString& strPath)
{
	m_strPath = strPath;
}

BOOL CMyDownload::Download()
{
	OpenSession();
	OpenConnection();
	OpenHttpFile();

	ReadFile();

	CloseHttpFile();
	CloseConnection();
	CloseSession();

	return m_bSuccess;
}



void CMyDownload::OpenSession()
{
	const int nTimeOut = 2000;
	m_session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut);
	m_session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 1);

	DWORD dwType;
	INTERNET_PORT wPort;
	CString strServer, strObject;	
	AfxParseURL(m_strUrl, dwType, strServer, strObject, wPort);

	ASSERT(dwType == AFX_INET_SERVICE_HTTPS || dwType == AFX_INET_SERVICE_HTTP);

	int pos = strObject.ReverseFind(_T('/'));
	CString strFile = strObject.Right(strObject.GetLength() - pos - 1);
	m_strFullFile = m_strPath + strFile;

	m_strServer = strServer;
	m_strObject = strObject;
	m_wPort = wPort;
	m_dwType = dwType;
}

void CMyDownload::CloseSession()
{
	m_session.Close();
}

void CMyDownload::OpenConnection()
{
	if (m_dwType == AFX_INET_SERVICE_HTTP)
	{
		m_pHttpConnection = m_session.GetHttpConnection(m_strServer, m_wPort);
	}
	else if (m_dwType == AFX_INET_SERVICE_HTTPS)
	{
		m_pHttpConnection = m_session.GetHttpConnection(m_strServer, INTERNET_FLAG_SECURE, m_wPort);
	}
}

void CMyDownload::CloseConnection()
{
	if (m_pHttpConnection)
	{
		m_pHttpConnection->Close();
		delete m_pHttpConnection;
		m_pHttpConnection = NULL;
	}
}

void CMyDownload::OpenHttpFile()
{
	if (m_pHttpConnection)
	{
		if (m_dwType == AFX_INET_SERVICE_HTTP)
		{
			m_pHttpFile = m_pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, m_strObject);
		}
		else if (m_dwType == AFX_INET_SERVICE_HTTPS)
		{
			m_pHttpFile = m_pHttpConnection->OpenRequest(CHttpConnection::HTTP_VERB_GET, m_strObject, NULL, 1, NULL, NULL,
				INTERNET_FLAG_SECURE | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_RELOAD |
				INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID);//SECURITY_FLAG_IGNORE_UNKNOWN_CA
		}
	}
}

void CMyDownload::CloseHttpFile()
{
	if (m_pHttpFile)
	{
		m_pHttpFile->Close();
		delete m_pHttpFile;
		m_pHttpFile = NULL;
	}
}

void CMyDownload::ReadFile()
{
	m_bSuccess = FALSE;
	if (m_pHttpFile == NULL)
		return;

	CString strHeaders("Content-Type: application/x-www-form-urlencoded");
	BOOL bRet = m_pHttpFile->SendRequest(strHeaders);
	if (!bRet)
		return;

	DWORD dwStateCode;
	m_pHttpFile->QueryInfoStatusCode(dwStateCode);
	if (dwStateCode != HTTP_STATUS_OK)
		return;

	HANDLE hFile = CreateFile(m_strFullFile, GENERIC_WRITE,
		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return;

	char szInfoBuffer[1000];
	DWORD dwFileSize = 0;
	DWORD dwInfoBufferSize = sizeof(szInfoBuffer);
	BOOL bResult = FALSE;
	bResult = m_pHttpFile->QueryInfo(HTTP_QUERY_CONTENT_LENGTH,
		(void*)szInfoBuffer, &dwInfoBufferSize, NULL);

	dwFileSize = atoi(szInfoBuffer);
	const int BUFFER_LENGTH = 1024 * 10;
	char* pszBuffer = new char[BUFFER_LENGTH];
	DWORD dwWrite, dwTotalWrite;
	dwWrite = dwTotalWrite = 0;
	UINT nRead = m_pHttpFile->Read(pszBuffer, BUFFER_LENGTH);

	while (nRead > 0)
	{
		Sleep(500);

		WriteFile(hFile, pszBuffer, nRead, &dwWrite, NULL);
		dwTotalWrite += dwWrite;
		nRead = m_pHttpFile->Read(pszBuffer, BUFFER_LENGTH);
	}

	delete[]pszBuffer;
	pszBuffer = NULL;

	CloseHandle(hFile);
	m_bSuccess = TRUE;
}




