
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "MyMFCProc.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if (m_ptE.x)
	{
		dc.Ellipse(m_ptE.x - 100, m_ptE.y - 100, m_ptE.x + 100, m_ptE.y + 100);
		dc.Rectangle(m_ptR.x - 100, m_ptR.y - 100, m_ptR.x + 100, m_ptR.y + 100);
	}

	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CClientDC dc(this);

	dc.Ellipse(point.x - 100, point.y - 100, point.x + 100, point.y + 100);
	m_ptE = point;


	CWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

    CClientDC dc(this);

    dc.Rectangle(point.x - 100, point.y - 100, point.x + 100, point.y + 100);
	m_ptR = point;

	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//GetParent()->PostMessageW(WM_COMMAND, MAKEWPARAM(ID_APP_ABOUT, 0), 0);

	//GetParent()->OnCmdMsg(ID_APP_ABOUT, 0, NULL, NULL);

	//AfxGetApp()->OnCmdMsg(ID_APP_ABOUT, 0, NULL, NULL);

	AfxGetMainWnd()->OnCmdMsg(ID_APP_ABOUT, 0, NULL, NULL);

	//OnCmdMsg(ID_APP_ABOUT, 0, NULL, NULL);

	CWnd::OnRButtonUp(nFlags, point);
}
