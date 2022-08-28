
// MyMFCDlgDlg.h : header file
//

#pragma once


// CMyMFCDlgDlg dialog
class CMyMFCDlgDlg : public CDialogEx
{
// Construction
public:
	CMyMFCDlgDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYMFCDLG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

	CStatic m_display1;
	CStatic m_display2;
	CButton m_counter1;
	CButton m_counter2;

	BOOL m_stop1;
	BOOL m_stop2;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton3();
};
