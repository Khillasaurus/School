// CMGfxDoc.cpp : implementation of the CCMGfxDoc class
//

#include "stdafx.h"
#include "CMGfx.h"

#include "CMGfxDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCMGfxDoc

IMPLEMENT_DYNCREATE(CCMGfxDoc, CRichEditDoc)

BEGIN_MESSAGE_MAP(CCMGfxDoc, CRichEditDoc)
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, &CRichEditDoc::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, &CRichEditDoc::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()


// CCMGfxDoc construction/destruction

CCMGfxDoc::CCMGfxDoc()
{
	// TODO: add one-time construction code here

}

CCMGfxDoc::~CCMGfxDoc()
{
}

BOOL CCMGfxDoc::OnNewDocument()
{
	if (!CRichEditDoc::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

CRichEditCntrItem* CCMGfxDoc::CreateClientItem(REOBJECT* preo) const
{
	return new CCMGfxCntrItem(preo, const_cast<CCMGfxDoc*>(this));
}




// CCMGfxDoc serialization

void CCMGfxDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}

	// Calling the base class CRichEditDoc enables serialization
	//  of the container document's COleClientItem objects.
	
	// Set CRichEditDoc::m_bRTF = FALSE because we want to serialize as text
	CRichEditDoc::m_bRTF = FALSE;
	CRichEditDoc::Serialize(ar);
}


// CCMGfxDoc diagnostics

#ifdef _DEBUG
void CCMGfxDoc::AssertValid() const
{
	CRichEditDoc::AssertValid();
}

void CCMGfxDoc::Dump(CDumpContext& dc) const
{
	CRichEditDoc::Dump(dc);
}
#endif //_DEBUG


// CCMGfxDoc commands
