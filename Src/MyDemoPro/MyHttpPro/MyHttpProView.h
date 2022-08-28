
// MyHttpProView.h : interface of the CMyHttpProView class
//

#pragma once


class CMyHttpProView : public CView
{
protected: // create from serialization only
	CMyHttpProView() noexcept;
	DECLARE_DYNCREATE(CMyHttpProView)

// Attributes
public:
	CMyHttpProDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMyHttpProView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyHttpProView.cpp
inline CMyHttpProDoc* CMyHttpProView::GetDocument() const
   { return reinterpret_cast<CMyHttpProDoc*>(m_pDocument); }
#endif

