
// MyMFCDlgDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MyMFCDlg.h"
#include "MyMFCDlgDlg.h"
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


// CMyMFCDlgDlg dialog



CMyMFCDlgDlg::CMyMFCDlgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYMFCDLG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyMFCDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_counter1);
	DDX_Control(pDX, IDC_BUTTON2, m_counter2);
	DDX_Control(pDX, IDC_STATIC1, m_display1);
	DDX_Control(pDX, IDC_STATIC2, m_display2);
	DDX_Control(pDX, IDC_BUTTON1, m_counter1);
	DDX_Control(pDX, IDC_BUTTON2, m_counter2);
}

BEGIN_MESSAGE_MAP(CMyMFCDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyMFCDlgDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyMFCDlgDlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CMyMFCDlgDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMyMFCDlgDlg message handlers

BOOL CMyMFCDlgDlg::OnInitDialog()
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
	m_counter1.SetWindowTextW(L"开始计数1");
	m_counter2.SetWindowTextW(L"开始计算2");

	m_display1.SetWindowTextW(L"0");
	m_display2.SetWindowTextW(L"0");

	m_stop1 = FALSE;
	m_stop2 = FALSE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyMFCDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyMFCDlgDlg::OnPaint()
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
HCURSOR CMyMFCDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyMFCDlgDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	if (m_stop1)
	{
		m_counter1.SetWindowTextW(L"开始计数1");
		KillTimer(101);
	}
	else
	{
		m_counter1.SetWindowTextW(L"停止计数1");
		SetTimer(101, 1000, nullptr);

		m_display1.SetWindowTextW(L"0");
	}

	m_stop1 = !m_stop1;
}


void CMyMFCDlgDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	if (m_stop2)
	{
		m_counter2.SetWindowTextW(L"开始计数2");
		KillTimer(102);
	}
	else
	{
		m_counter2.SetWindowTextW(L"停止计数2");
		SetTimer(102, 1000, nullptr);

		m_display2.SetWindowTextW(L"0");
	}

	m_stop2 = !m_stop2;
}


void CMyMFCDlgDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 101)
	{
		CString strTxt;
		m_display1.GetWindowTextW(strTxt);

		int value = _wtoi(strTxt);
		value++;

		strTxt.Format(L"%d", value);
		m_display1.SetWindowTextW(strTxt);
	}
	else if (nIDEvent == 102)
	{
		CString strTxt;
		m_display2.GetWindowTextW(strTxt);

		int value = _wtoi(strTxt);
		value++;

		strTxt.Format(L"%d", value);
		m_display2.SetWindowTextW(strTxt);
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CMyMFCDlgDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CString strTxt;
	m_display1.GetWindowTextW(strTxt);
	int value1 = _wtoi(strTxt);

	m_display2.GetWindowTextW(strTxt);
	int value2 = _wtoi(strTxt);

	int value = value1 > value2 ? value1 : value2;
	strTxt.Format(L"%d", value);
	m_display1.SetWindowTextW(strTxt);
	m_display2.SetWindowTextW(strTxt);
}
