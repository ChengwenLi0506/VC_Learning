
// MyHttpProDoc.h : interface of the CMyHttpProDoc class
//


#pragma once


class CMyHttpProDoc : public CDocument
{
protected: // create from serialization only
	CMyHttpProDoc() noexcept;
	DECLARE_DYNCREATE(CMyHttpProDoc)

// Attributes
public:
	HGLOBAL m_hglobal = NULL;
	IStream* m_stream = NULL;
	IPicture* m_picture = NULL;

// Operations
public:
	void ReadContent(CArchive& ar);
	void ReleaseContent();

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMyHttpProDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};
