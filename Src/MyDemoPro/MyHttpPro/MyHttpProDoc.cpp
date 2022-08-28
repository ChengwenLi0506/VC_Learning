
// MyHttpProDoc.cpp : implementation of the CMyHttpProDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MyHttpPro.h"
#endif

#include "MyHttpProDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyHttpProDoc

IMPLEMENT_DYNCREATE(CMyHttpProDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyHttpProDoc, CDocument)
END_MESSAGE_MAP()


// CMyHttpProDoc construction/destruction

CMyHttpProDoc::CMyHttpProDoc() noexcept
{
	// TODO: add one-time construction code here

}

CMyHttpProDoc::~CMyHttpProDoc()
{
	ReleaseContent();
}

BOOL CMyHttpProDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CMyHttpProDoc serialization

void CMyHttpProDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
		ReadContent(ar);
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMyHttpProDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMyHttpProDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMyHttpProDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMyHttpProDoc diagnostics

#ifdef _DEBUG
void CMyHttpProDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyHttpProDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyHttpProDoc commands


BOOL CMyHttpProDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	ReleaseContent();

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here


	return TRUE;
}


void CMyHttpProDoc::ReadContent(CArchive& ar)
{
	if (m_hglobal)
		return;

	CFile* pFile = ar.GetFile();
	if (pFile == NULL)
		return;

	DWORD dwLen = (DWORD)pFile->GetLength();
	m_hglobal = GlobalAlloc(GMEM_MOVEABLE, dwLen);
	if (m_hglobal == NULL)
		return;

	LPVOID pvdata = GlobalLock(m_hglobal);
	pFile->Read(pvdata, dwLen);
	GlobalUnlock(m_hglobal);

	CreateStreamOnHGlobal(m_hglobal, TRUE, &m_stream);
	if (m_stream == NULL)
		return;

	OleLoadPicture(m_stream, dwLen, TRUE, IID_IPicture, (LPVOID*)&m_picture);
	if (m_picture == NULL)
		return;

	OLE_XSIZE_HIMETRIC m_width;
	OLE_YSIZE_HIMETRIC m_height;
	m_picture->get_Width(&m_width);
	m_picture->get_Height(&m_height);
}

void CMyHttpProDoc::ReleaseContent()
{
	if (m_picture)
	{
		m_picture->Release();
		m_picture = NULL;
	}

	if (m_stream)
	{
		m_stream->Release();
		m_stream = NULL;
	}
	
	if (m_hglobal)
	{
		GlobalFree(m_hglobal);
		m_hglobal = NULL;
	}
}
