// CntrItem.cpp : implementation of the CCMGfxCntrItem class
//

#include "stdafx.h"
#include "CMGfx.h"

#include "CMGfxDoc.h"
#include "CMGfxView.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCMGfxCntrItem implementation

IMPLEMENT_SERIAL(CCMGfxCntrItem, CRichEditCntrItem, 0)

CCMGfxCntrItem::CCMGfxCntrItem(REOBJECT* preo, CCMGfxDoc* pContainer)
	: CRichEditCntrItem(preo, pContainer)
{
	// TODO: add one-time construction code here
}

CCMGfxCntrItem::~CCMGfxCntrItem()
{
	// TODO: add cleanup code here
}


// CCMGfxCntrItem diagnostics

#ifdef _DEBUG
void CCMGfxCntrItem::AssertValid() const
{
	CRichEditCntrItem::AssertValid();
}

void CCMGfxCntrItem::Dump(CDumpContext& dc) const
{
	CRichEditCntrItem::Dump(dc);
}
#endif

