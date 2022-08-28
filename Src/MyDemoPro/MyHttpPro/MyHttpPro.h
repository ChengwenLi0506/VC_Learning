
// MyHttpPro.h : main header file for the MyHttpPro application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMyHttpProApp:
// See MyHttpPro.cpp for the implementation of this class
//

class CMyHttpProApp : public CWinApp
{
public:
	CMyHttpProApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileDownload();
	afx_msg void OnOpenDocument();

public:
	void DoDownload();
	void DownloadUrl();

	CString m_strUrl;
	CString m_strPath;
	CString m_strFile;
};

extern CMyHttpProApp theApp;

UINT MyThreadProc(LPVOID pParam);
