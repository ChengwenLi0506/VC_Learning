
// MyChatProDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MyChatPro.h"
#include "MyChatProDlg.h"
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


// CMyChatProDlg dialog



CMyChatProDlg::CMyChatProDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYCHATPRO_DIALOG, pParent)
	, m_sockServer(this)
	, m_sockClient(this)
	, m_sockData(this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyChatProDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_IP, m_ip);
	DDX_Control(pDX, IDC_EDIT_PORT, m_port);
	DDX_Control(pDX, IDC_RICHEDIT2_OUTPUT, m_output);
	DDX_Control(pDX, IDC_RICHEDIT2_INPUT, m_input);
}

BEGIN_MESSAGE_MAP(CMyChatProDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CMyChatProDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_NET, &CMyChatProDlg::OnBnClickedButtonNet)
	ON_COMMAND(IDC_RADIO_CLIENT, &CMyChatProDlg::OnRadioClient)
	ON_COMMAND(IDC_RADIO_SERVER, &CMyChatProDlg::OnRadioServer)
END_MESSAGE_MAP()


// CMyChatProDlg message handlers

BOOL CMyChatProDlg::OnInitDialog()
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
	m_ip.SetWindowTextW(_T("127.0.0.1"));
	m_port.SetWindowTextW(_T("80"));

	SetChatServer(TRUE);
	StopNetwork();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyChatProDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyChatProDlg::OnPaint()
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
HCURSOR CMyChatProDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyChatProDlg::SetChatServer(BOOL bServer)
{
	// TODO: Add your implementation code here
	CString strType;
	if (bServer)
	{
		((CButton*)GetDlgItem(IDC_RADIO_SERVER))->SetCheck(TRUE);
		strType = _T(" - Chat Server");
		
	}
	else
	{
		((CButton*)GetDlgItem(IDC_RADIO_CLIENT))->SetCheck(TRUE);
		strType = _T(" - Chat Client");
	}

	CString strTitle = _T("My Chat Application") + strType;
	SetWindowTextW(strTitle);
}

void CMyChatProDlg::OnBnClickedButtonSend()
{
	// TODO: Add your control notification handler code here

	// Get message from input box
	CString strMsg;
	m_input.GetWindowTextW(strMsg);
	if (strMsg.GetLength() == 0)
		return;

	m_input.SetWindowTextW(_T(""));

	// Show message in output box
	ShowMessage(strMsg);

	// Send message to remote
	SendData(strMsg);
}


void CMyChatProDlg::OnBnClickedButtonNet()
{
	// TODO: Add your control notification handler code here
	if (m_bStart)
	{
		StopNetwork();
	}
	else
	{
		StartNetwork();
	}
}


void CMyChatProDlg::StartNetwork()
{
	// TODO: Add your implementation code here.
	CString strTmp;
	m_ip.GetWindowTextW(strTmp);
	if (strTmp.GetLength() == 0)
		return;

	m_strIp = strTmp;

	m_port.GetWindowTextW(strTmp);
	if (strTmp.GetLength() == 0)
		return;

	m_dwPort = _wtoi(strTmp);

	BOOL bSucced = FALSE;
	if (isServer())
		bSucced = StartServer();
	else
		bSucced = StartClient();

	if (!bSucced)
	{
		StopNetwork();
		return;
	}

	m_bStart = TRUE;

	//GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_NET)->SetWindowTextW(_T("Stop"));

	GetDlgItem(IDC_RADIO_SERVER)->EnableWindow(FALSE);
	GetDlgItem(IDC_RADIO_CLIENT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_IP)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(FALSE);
}


void CMyChatProDlg::StopNetwork()
{
	// TODO: Add your implementation code here.
	m_bStart = FALSE;

	//GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_NET)->SetWindowTextW(_T("Start"));

	GetDlgItem(IDC_RADIO_SERVER)->EnableWindow(TRUE);
	GetDlgItem(IDC_RADIO_CLIENT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_IP)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_PORT)->EnableWindow(TRUE);

	if (isServer())
		StopServer();
	else
		StopClient();
}

BOOL CMyChatProDlg::isServer()
{
	int check = ((CButton*)GetDlgItem(IDC_RADIO_SERVER))->GetCheck();
	return (check == 1);
}

BOOL CMyChatProDlg::StartServer()
{
	DWORD dwErr = 0;

	BOOL ret = m_sockServer.Create(m_dwPort);
	if (!ret)
	{
		dwErr = GetLastError();
		return FALSE;
	}

	ret = m_sockServer.Listen();
	if (!ret)
		return FALSE;

	// Accept will stop here, wait client to connect
	// so must put into a thread to do
	// or 
	// AsyncSelect will request event notification for a socket
	ret = m_sockServer.AsyncSelect();
	if (!ret)
		return FALSE;

	m_sockServer.Prepare();
	return TRUE;
}

void CMyChatProDlg::StopServer()
{
	m_sockServer.Close();
	m_sockData.Close();
}

BOOL CMyChatProDlg::StartClient()
{
	DWORD dwErr = 0;

	BOOL ret = m_sockClient.Create();  
	if (!ret)
	{
		dwErr = GetLastError();
		return FALSE;
	}

	ret = m_sockClient.Connect(m_strIp, m_dwPort);
	if (!ret)
	{
		dwErr = GetLastError();
		if (dwErr == WSAECONNREFUSED)
			AfxMessageBox(_T("Please start chat server first!"));

		return FALSE;
	}

	// AsyncSelect will request event notification for a socket
	ret = m_sockClient.AsyncSelect();
	if (!ret)
		return FALSE;

	m_sockClient.Prepare();
	return TRUE;
}

void CMyChatProDlg::StopClient()
{
	m_sockClient.Close();
}

void CMyChatProDlg::AcceptConnect()
{
	m_sockServer.Accept(m_sockData);
	
	m_sockData.AsyncSelect();
	m_sockData.Prepare();
}

void CMyChatProDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
	Clear();
}


void CMyChatProDlg::Clear()
{
	StopClient();
	StopServer();
}

void CMyChatProDlg::ReceiveData(CString& strData)
{
	ShowMessage(strData, FALSE);
}

void CMyChatProDlg::SendData(CString& strData)
{
	if (isServer())
	{
		m_sockData.SendMessage(strData);
	}
	else
	{
		m_sockClient.SendMessage(strData);
	}
}


void CMyChatProDlg::OnRadioClient()
{
	// TODO: Add your command handler code here
	SetChatServer(FALSE);
}


void CMyChatProDlg::OnRadioServer()
{
	// TODO: Add your command handler code here
	SetChatServer(TRUE);
}


BOOL CMyChatProDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	// press ESC key
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	// press RETURN key
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		CWnd* pFocus = GetFocus();
		if (pFocus)
		{
			// focus on input box, then simulate to click send button
			if (m_input.m_hWnd == pFocus->m_hWnd)
			{
				WPARAM wParam;
				LPARAM lParam;

				wParam = MAKEWPARAM(IDC_BUTTON_SEND, BN_CLICKED);
				lParam = (LPARAM)GetDlgItem(IDC_BUTTON_SEND)->m_hWnd;
				PostMessageW(WM_COMMAND, wParam, lParam);
			}
		}


		return TRUE;
	}


	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMyChatProDlg::ShowMessage(CString& strMsg, BOOL bLocal)
{
	COLORREF color = bLocal ? RGB(255, 0, 0) : RGB(0, 0, 255);
	CString strPre = bLocal ? _T("  Me: ") : _T(" You: ");
	CString strContent = strPre + strMsg +_T("\r\n");

	long start1, start2;
	long end1, end2;
	m_output.SetSel(-1, -1);
	m_output.GetSel(start1, end1);

	m_output.ReplaceSel(strContent);

	m_output.GetSel(start2, end2);
	//TRACE("******start1:%d, end1:%d, start2:%d, end2:%d\n", start1, end1, start2, end2);

	// set the message format
	m_output.SetSel(start1, end2);

	CHARFORMAT cf;
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_COLOR;	// CFM_STRIKEOUT | CFM_BOLD | CFM_COLOR;
	cf.crTextColor = color;
	cf.dwEffects = CFE_BOLD;
	m_output.SetSelectionCharFormat(cf);

	// auto scroll to bottom
	m_output.PostMessage(WM_VSCROLL, SB_BOTTOM, 0);
}

