
// MyMFCProc.h : main header file for the MyMFCProc application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMyMFCProcApp:
// See MyMFCProc.cpp for the implementation of this class
//

class CMyMFCProcApp : public CWinApp
{
public:
	CMyMFCProcApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyMFCProcApp theApp;
