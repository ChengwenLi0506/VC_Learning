
// MyThreadDlg.h : header file
//

#pragma once


// CMyThreadDlg dialog
class CMyThreadDlg : public CDialogEx
{
// Construction
public:
	CMyThreadDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYTHREAD_DIALOG };
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
	// button 1
	CButton m_button1;
	CStatic m_display1;
	int m_counter1;
	void ShowCount1();
	afx_msg void OnBnClickedButton1();

	// button 2
	CButton m_button2;
	CStatic m_display2;
	int m_counter2;
	void ShowCount2();
	afx_msg void OnBnClickedButton2();

	// button 2 thread
	CWinThread* m_pthread = nullptr;
	void ThreadRun();
	static UINT __cdecl MyThreadProc(LPVOID pParam);
	BOOL m_bExit = FALSE;
	void WaitThreadExit();

	// close command
	virtual void OnCancel();
	virtual void OnOK();

	// button 3
	CButton m_button3;
	CStatic m_display3;
	int m_counter3;
	void ShowCount3();
	afx_msg void OnBnClickedButton3();

	// button 3 thread
	CWinThread* m_pthread2 = nullptr;
	void ThreadRun2();
	static UINT __cdecl MyThreadProc2(LPVOID pParam);
	CEvent m_event;
};




