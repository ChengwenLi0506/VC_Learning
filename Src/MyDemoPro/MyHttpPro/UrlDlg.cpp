// CUrlDlg.cpp : implementation file
//

#include "pch.h"
#include "MyHttpPro.h"
#include "afxdialogex.h"
#include "UrlDlg.h"


// CUrlDlg dialog

IMPLEMENT_DYNAMIC(CUrlDlg, CDialogEx)

CUrlDlg::CUrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_URLBOX, pParent)
{

}

CUrlDlg::~CUrlDlg()
{
}

void CUrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_URL, m_url);
}


BEGIN_MESSAGE_MAP(CUrlDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUrlDlg::OnBnClickedOk)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CUrlDlg message handlers


void CUrlDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_url.GetWindowTextW(m_strUrl);

	CDialogEx::OnOK();
}



BOOL CUrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_strUrl = _T("https://pic.rmb.bdstatic.com/0003ab80203c710e791de55fb0268655.jpeg");
	m_url.SetWindowTextW(m_strUrl);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
