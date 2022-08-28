
// MyThread2Dlg.h : header file
//

#pragma once


// CMyThread2Dlg dialog
class CMyThread2Dlg : public CDialogEx
{
// Construction
public:
	CMyThread2Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYTHREAD2_DIALOG };
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
	CButton m_button;
	CStatic m_display1;
	CStatic m_display2;
	afx_msg void OnBnClickedButton1();

	BOOL m_bRun = FALSE;
	CWinThread* m_aThread[2] = {nullptr};
	static UINT __cdecl MyThreadProc(LPVOID pParam);
	void ThreadRun(int tid);
	void ShowCount(int id);
	CEvent m_event1;
	CEvent m_event2;


	virtual void OnCancel();
	virtual void OnOK();
	void CheckThreadExit();


	int m_value;
	CStatic m_share;
	void ShowValue();
};

class CThreadParam
{
public:
	CMyThread2Dlg* pDlg;
	int tid;
};


