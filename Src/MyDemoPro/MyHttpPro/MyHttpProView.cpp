
// MyHttpProView.cpp : implementation of the CMyHttpProView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MyHttpPro.h"
#endif

#include "MyHttpProDoc.h"
#include "MyHttpProView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyHttpProView

IMPLEMENT_DYNCREATE(CMyHttpProView, CView)

BEGIN_MESSAGE_MAP(CMyHttpProView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMyHttpProView construction/destruction

CMyHttpProView::CMyHttpProView() noexcept
{
	// TODO: add construction code here

}

CMyHttpProView::~CMyHttpProView()
{
}

BOOL CMyHttpProView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMyHttpProView drawing

void CMyHttpProView::OnDraw(CDC* pDC)
{
	CMyHttpProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	IPicture* picture = pDoc->m_picture;
	if (picture == NULL)
		return;

	OLE_XSIZE_HIMETRIC width;
	OLE_YSIZE_HIMETRIC height;

	picture->get_Width(&width);
	picture->get_Height(&height);

	CRect rect;
	GetClientRect(rect);
	SetScrollRange(SB_VERT, 0, (int)(height / 26.45) - rect.Height());
	SetScrollRange(SB_HORZ, 0, (int)(width / 26.45) - rect.Width());

	picture->Render(*pDC, 1, 1, rect.Width(), rect.Height(), 0, height, width, -height, NULL);
}


// CMyHttpProView printing

BOOL CMyHttpProView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyHttpProView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyHttpProView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMyHttpProView diagnostics

#ifdef _DEBUG
void CMyHttpProView::AssertValid() const
{
	CView::AssertValid();
}

void CMyHttpProView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyHttpProDoc* CMyHttpProView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyHttpProDoc)));
	return (CMyHttpProDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyHttpProView message handlers
