
// MyThread2Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MyThread2.h"
#include "MyThread2Dlg.h"
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


// CMyThread2Dlg dialog



CMyThread2Dlg::CMyThread2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYTHREAD2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyThread2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_button);
	DDX_Control(pDX, IDC_STATIC1, m_display1);
	DDX_Control(pDX, IDC_STATIC2, m_display2);
	DDX_Control(pDX, IDC_STATIC3, m_share);
}

BEGIN_MESSAGE_MAP(CMyThread2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyThread2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMyThread2Dlg message handlers

BOOL CMyThread2Dlg::OnInitDialog()
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
	m_button.SetWindowTextW(L"Create thread");
	m_display1.SetWindowTextW(L"0");
	m_display2.SetWindowTextW(L"0");

	m_share.SetWindowTextW(L"0");
	m_value = 0;

	// bring the dialog to topmost
	BringWindowToTop();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyThread2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyThread2Dlg::OnPaint()
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
HCURSOR CMyThread2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyThread2Dlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	if (m_aThread[0] == nullptr)
	{
		// create two new thread to run
		for (int i = 0; i < 2; i++)
		{
			CThreadParam* pParam = new CThreadParam();
			pParam->pDlg = this;
			pParam->tid = i;

			m_aThread[i] = AfxBeginThread(MyThreadProc, pParam);
		}

		m_bRun = TRUE;
		m_button.SetWindowTextW(L"Suspend thread");
	}
	else
	{
		// run status
		if (m_bRun)
		{
			m_bRun = FALSE;
			m_button.SetWindowTextW(L"Resume thread");

			// pause a thread run
			m_aThread[0]->SuspendThread();	
			m_aThread[1]->SuspendThread();
		}
		// pause status
		else
		{
			m_bRun = TRUE;
			m_button.SetWindowTextW(L"Suspend thread");

			// re-start a thread run
			m_aThread[0]->ResumeThread();	
			m_aThread[1]->ResumeThread();
		}	
	}
}

UINT __cdecl CMyThread2Dlg::MyThreadProc(LPVOID pParam)
{
	OutputDebugString(L"Thread Start\n");

	CThreadParam* p = (CThreadParam*)pParam;
	if (p)
	{
		p->pDlg->ThreadRun(p->tid + 1);

		delete p;
	}

	OutputDebugString(L"Thread End\n");
	return 0;
}



void CMyThread2Dlg::ThreadRun(int tid)
{
	// TODO: Add your implementation code here.
	while(TRUE)// (int i = 0; i < 1000; i++)
	{
		ShowCount(tid);

		// for exit
		HANDLE hHandle = (tid == 1 ? m_event1 : m_event2);
		DWORD dwWaitResult = WaitForSingleObject(hHandle, 0);
		if (dwWaitResult == WAIT_OBJECT_0)
		{
			OutputDebugString(L"WAIT_OBJECT_0\n");
			break;
		}
	}

}


void CMyThread2Dlg::ShowCount(int id)
{
	// TODO: Add your implementation code here.
	CStatic* p = (id == 1 ? &m_display1 : &m_display2);

	CString strTxt;
	p->GetWindowTextW(strTxt);
	int n = _wtoi(strTxt);
	n++;

	strTxt.Format(L"%d", n);
	p->SetWindowTextW(strTxt);


	ShowValue();
}


void CMyThread2Dlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	CheckThreadExit();

	CDialogEx::OnCancel();
}


void CMyThread2Dlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	CheckThreadExit();

	CDialogEx::OnOK();
}

void CMyThread2Dlg::CheckThreadExit()
{
	if (m_aThread[0] == nullptr)
		return;

	m_event1.SetEvent();
	m_event2.SetEvent();


	ShowWindow(SW_HIDE);
	Sleep(1000);

	OutputDebugString(L"CheckThreadExit\n");
}




void CMyThread2Dlg::ShowValue()
{
	m_value++;
	CString strTxt;

	strTxt.Format(L"%d", m_value);
	m_share.SetWindowTextW(strTxt);
}