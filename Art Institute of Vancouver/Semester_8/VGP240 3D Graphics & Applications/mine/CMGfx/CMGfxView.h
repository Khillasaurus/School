// CMGfxView.h : interface of the CCMGfxView class
//


#pragma once

class CCMGfxCntrItem;

class CCMGfxView : public CRichEditView
{
protected: // create from serialization only
	CCMGfxView();
	DECLARE_DYNCREATE(CCMGfxView)

// Attributes
public:
	CCMGfxDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCMGfxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnDestroy();
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CMGfxView.cpp
inline CCMGfxDoc* CCMGfxView::GetDocument() const
   { return reinterpret_cast<CCMGfxDoc*>(m_pDocument); }
#endif

