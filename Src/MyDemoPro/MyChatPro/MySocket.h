#pragma once
#include "afxsock.h"

class CMyChatProDlg;

// CMySocket command target
enum SOCKET_STATUS
{
	SS_INIT = 0,
	SS_HELLO = 1,
	SS_WORK = 2,
};

class CMySocket : public CSocket
{
public:
	CMySocket(CMyChatProDlg* dlg);
	virtual ~CMySocket();

	// AsnycSelect will receive the following callback
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);

	void Prepare();
	void SayHello();

	void ReceiveMessage();
	void SendMessage(CString& strMsg);

private:
	CMyChatProDlg* m_dlg;
	SOCKET_STATUS m_status{ SS_INIT };
};


