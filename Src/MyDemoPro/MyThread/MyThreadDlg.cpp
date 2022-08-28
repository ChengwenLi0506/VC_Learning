
// MyThreadDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MyThread.h"
#include "MyThreadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyThreadDlg dialog



CMyThreadDlg::CMyThreadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYTHREAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_button1);
	DDX_Control(pDX, IDC_STATIC1, m_display1);
	DDX_Control(pDX, IDC_BUTTON2, m_button2);
	DDX_Control(pDX, IDC_STATIC2, m_display2);
	DDX_Control(pDX, IDCANCEL, m_button3);
	DDX_Control(pDX, IDC_STATIC3, m_display3);
}

BEGIN_MESSAGE_MAP(CMyThreadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyThreadDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyThreadDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyThreadDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMyThreadDlg message handlers

BOOL CMyThreadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_counter1 = 0;
	ShowCount1();

	m_counter2 = 0;
	ShowCount2();

	m_counter3 = 0;
	ShowCount3();


	// bring the dialog to topmost
	BringWindowToTop();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyThreadDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyThreadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyThreadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMyThreadDlg::ShowCount1()
{
	// TODO: Add your implementation code here.
	CString strTxt;
	strTxt.Format(L"%d", m_counter1);

	m_display1.SetWindowTextW(strTxt);
}

void CMyThreadDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here

	for (int i = 0; i < 50; i++)
	{
		m_counter1++;
		ShowCount1();

		Sleep(1000);
	}
}




void CMyThreadDlg::ShowCount2()
{
	// TODO: Add your implementation code here.
	CString strTxt;
	strTxt.Format(L"%d", m_counter2);

	m_display2.SetWindowTextW(strTxt);
}


void CMyThreadDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	// create a thread, let this thread to do
	if (m_pthread)
		return;

	m_pthread = AfxBeginThread(MyThreadProc, this);
}


void CMyThreadDlg::ThreadRun()
{
	for (int i = 0; i < 50; i++)
	{
		m_counter2++;
		ShowCount2();

		if (m_bExit)
			break;

		Sleep(1000);
	}

	m_pthread = nullptr;
}

void CMyThreadDlg::WaitThreadExit()
{
	if (m_pthread2)
	{
		// Sets the event to available (signaled) 
		// and releases any waiting threads.
		m_event.SetEvent();
	}
	
	

	if (m_pthread)
	{
		m_bExit = TRUE;
		Sleep(1000);
	}
}

UINT __cdecl CMyThreadDlg::MyThreadProc(LPVOID pParam)
{
	OutputDebugString(L"Thread Start\n");

	CMyThreadDlg* pDlg = (CMyThreadDlg*)pParam;
	if (pDlg)
	{
		pDlg->ThreadRun();
	}

	OutputDebugString(L"Thread End\n");
	return 0;
}



void CMyThreadDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	OutputDebugString(L"OnCancel\n");

	WaitThreadExit();
	
	CDialogEx::OnCancel();
}


void CMyThreadDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	OutputDebugString(L"OnOK\n");

	WaitThreadExit();

	CDialogEx::OnOK();
}



void CMyThreadDlg::ShowCount3()
{
	CString strTxt;
	strTxt.Format(L"%d", m_counter3);

	m_display3.SetWindowTextW(strTxt);
}

void CMyThreadDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here

	// create a thread, let this thread to do
	if (m_pthread2)
		return;

	m_pthread2 = AfxBeginThread(MyThreadProc2, this);
}


void CMyThreadDlg::ThreadRun2()
{
	/*
	// same as the button 2
	for (int i = 0; i < 50; i++)
	{
		m_counter3++;
		ShowCount3();

		if (m_bExit)
			break;

		// the key important is this sentence
		Sleep(1000);
	}
	*/

	for (int i = 0; i < 50; i++)
	{
		m_counter3++;
		ShowCount3();

		DWORD dwWaitResult = WaitForSingleObject(m_event, 1000);
		if (dwWaitResult == WAIT_OBJECT_0)
			break;
	}

	m_pthread2 = nullptr;
}

UINT __cdecl CMyThreadDlg::MyThreadProc2(LPVOID pParam)
{
	OutputDebugString(L"Thread2 Start\n");

	CMyThreadDlg* pDlg = (CMyThreadDlg*)pParam;
	if (pDlg)
	{
		pDlg->ThreadRun2();
	}

	OutputDebugString(L"Thread2 End\n");
	return 0;
}

