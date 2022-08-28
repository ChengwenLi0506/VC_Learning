#pragma once
#include "afxdialogex.h"


// CUrlDlg dialog

class CUrlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUrlDlg)

public:
	CUrlDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUrlDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_URLBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_url;
	afx_msg void OnBnClickedOk();
	CString m_strUrl;
	virtual BOOL OnInitDialog();
};
