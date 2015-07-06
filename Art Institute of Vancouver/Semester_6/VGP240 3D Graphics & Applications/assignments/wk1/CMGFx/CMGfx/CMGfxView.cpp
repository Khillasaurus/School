// CMGfxView.cpp : implementation of the CCMGfxView class
//

#include "stdafx.h"
#include "CMGfx.h"

#include "CMGfxDoc.h"
#include "CntrItem.h"
#include "CMGfxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCMGfxView

IMPLEMENT_DYNCREATE(CCMGfxView, CRichEditView)

BEGIN_MESSAGE_MAP(CCMGfxView, CRichEditView)
	ON_WM_DESTROY()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRichEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CRichEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCMGfxView construction/destruction

CCMGfxView::CCMGfxView()
{
	// TODO: add construction code here

}

CCMGfxView::~CCMGfxView()
{
}

BOOL CCMGfxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRichEditView::PreCreateWindow(cs);
}

void CCMGfxView::OnInitialUpdate()
{
	CRichEditView::OnInitialUpdate();


	// Set the printing margins (720 twips = 1/2 inch)
	SetMargins(CRect(720, 720, 720, 720));
}


// CCMGfxView printing

BOOL CCMGfxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}


void CCMGfxView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
   CRichEditView::OnDestroy();
}



// CCMGfxView diagnostics

#ifdef _DEBUG
void CCMGfxView::AssertValid() const
{
	CRichEditView::AssertValid();
}

void CCMGfxView::Dump(CDumpContext& dc) const
{
	CRichEditView::Dump(dc);
}

CCMGfxDoc* CCMGfxView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCMGfxDoc)));
	return (CCMGfxDoc*)m_pDocument;
}
#endif //_DEBUG


// CCMGfxView message handlers
