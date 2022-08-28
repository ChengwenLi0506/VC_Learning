// MySocket.cpp : implementation file
//

#include "pch.h"
#include "MyChatPro.h"
#include "MySocket.h"
#include "MyChatProDlg.h"


// CMySocket

CMySocket::CMySocket(CMyChatProDlg* dlg)
	: m_dlg(dlg)
{
}

CMySocket::~CMySocket()
{
}


// CMySocket member functions

void CMySocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE("OnAccept, Code: %d\n", nErrorCode);
	m_dlg->AcceptConnect();

	CSocket::OnAccept(nErrorCode);
}


void CMySocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE("OnClose, Code: %d\n", nErrorCode);
	m_dlg->StopNetwork();

	CSocket::OnClose(nErrorCode);
}


void CMySocket::OnConnect(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE("OnConnect, Code: %d\n", nErrorCode);
	// no need any operation

	CSocket::OnConnect(nErrorCode);
}


void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE("OnReceive, Code: %d\n", nErrorCode);
	// can receive data from socket
	ReceiveMessage();

	CSocket::OnReceive(nErrorCode);
}


void CMySocket::OnSend(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	TRACE("OnSend, Code: %d\n", nErrorCode);
	// can send data to socket
	if (m_status == SS_HELLO)
	{
		m_status = SS_WORK;
		SayHello();
	}

	CSocket::OnSend(nErrorCode);
}



void CMySocket::Prepare()
{
	m_status = SS_HELLO;
}

void CMySocket::SayHello()
{
	CString strHello;
	if (m_dlg->isServer())
	{
		strHello = _T("Hello, this is a chat server. ");
	}
	else
	{
		strHello = _T("Hello, this is a chat client. ");
	}

	SendMessage(strHello);
}

void CMySocket::ReceiveMessage()
{
	TCHAR buff[4096] = { 0 };
	int nRead;
	nRead = Receive(buff, 4096);

	CString strData = buff;
	m_dlg->ReceiveData(strData);
}

void CMySocket::SendMessage(CString& strMsg)
{
	if (m_status == SS_WORK)
	{
		int len = strMsg.GetLength() * sizeof(TCHAR);
		int ret = Send(strMsg, len);
		ASSERT(len == ret);
	}
}

