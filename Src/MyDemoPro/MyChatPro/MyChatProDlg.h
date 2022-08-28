
// MyChatProDlg.h : header file
//

#pragma once

#include "MySocket.h"

// CMyChatProDlg dialog
class CMyChatProDlg : public CDialogEx
{
// Construction
public:
	CMyChatProDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYCHATPRO_DIALOG };
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
private:
	void Clear();

public:
	CEdit m_ip;
	CEdit m_port;
	CRichEditCtrl m_output;
	CRichEditCtrl m_input;

	void SetChatServer(BOOL bServer);
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonNet();

	void StartNetwork();
	void StopNetwork();

	BOOL isServer();
	BOOL StartServer();
	void StopServer();
	BOOL StartClient();
	void StopClient();
	void AcceptConnect();

	CString m_strIp;
	DWORD m_dwPort;
	BOOL m_bStart = FALSE;

	CMySocket m_sockServer;
	CMySocket m_sockClient;
	CMySocket m_sockData;

	afx_msg void OnDestroy();

	void ReceiveData(CString& strData);
	void SendData(CString& strData);
	afx_msg void OnRadioClient();
	afx_msg void OnRadioServer();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void ShowMessage(CString& strMsg, BOOL bLocal = TRUE);
};
