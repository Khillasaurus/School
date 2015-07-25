// CMGfxDoc.h : interface of the CCMGfxDoc class
//


#pragma once


class CCMGfxDoc : public CRichEditDoc
{
protected: // create from serialization only
	CCMGfxDoc();
	DECLARE_DYNCREATE(CCMGfxDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual CRichEditCntrItem* CreateClientItem(REOBJECT* preo) const;

// Implementation
public:
	virtual ~CCMGfxDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


