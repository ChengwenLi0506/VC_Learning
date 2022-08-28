
// MyThread2.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMyThread2App:
// See MyThread2.cpp for the implementation of this class
//

class CMyThread2App : public CWinApp
{
public:
	CMyThread2App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMyThread2App theApp;
