// CntrItem.h : interface of the CCMGfxCntrItem class
//

#pragma once

class CCMGfxDoc;
class CCMGfxView;

class CCMGfxCntrItem : public CRichEditCntrItem
{
	DECLARE_SERIAL(CCMGfxCntrItem)

// Constructors
public:
	CCMGfxCntrItem(REOBJECT* preo = NULL, CCMGfxDoc* pContainer = NULL);
		// Note: pContainer is allowed to be NULL to enable IMPLEMENT_SERIALIZE
		//  IMPLEMENT_SERIALIZE requires the class have a constructor with
		//  zero arguments.  Normally, OLE items are constructed with a
		//  non-NULL document pointer

// Attributes
public:
	CCMGfxDoc* GetDocument()
		{ return reinterpret_cast<CCMGfxDoc*>(CRichEditCntrItem::GetDocument()); }
	CCMGfxView* GetActiveView()
		{ return reinterpret_cast<CCMGfxView*>(CRichEditCntrItem::GetActiveView()); }

	public:
	protected:

// Implementation
public:
	~CCMGfxCntrItem();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

