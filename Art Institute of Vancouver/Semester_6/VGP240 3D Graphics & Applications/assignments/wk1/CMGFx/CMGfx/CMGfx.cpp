// CMGfx.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "CMGfx.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "CMGfxDoc.h"
#include "CMGfxView.h"

#include "oglMFCDialogDlg.h"

#include "Rasterizer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCMGfxApp

BEGIN_MESSAGE_MAP(CCMGfxApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CCMGfxApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_GRAPHICS_DISPLAYWINDOW, &CCMGfxApp::OnGraphicsDisplaywindow)
END_MESSAGE_MAP()


// CCMGfxApp construction

CCMGfxApp::CCMGfxApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CCMGfxApp object

CCMGfxApp theApp;


// CCMGfxApp initialization

BOOL CCMGfxApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_CMGfxTYPE,
		RUNTIME_CLASS(CCMGfxDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CCMGfxView));
	if (!pDocTemplate)
		return FALSE;
	pDocTemplate->SetContainerInfo(IDR_CMGfxTYPE_CNTR_IP);
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// call DragAcceptFiles only if there's a suffix
	//  In an MDI app, this should occur immediately after setting m_pMainWnd
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CCMGfxApp::ExitInstance()
{
	DeleteSingletons();
	return CWinApp::ExitInstance();
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CCMGfxApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CCMGfxApp message handlers


void CCMGfxApp::OnGraphicsDisplaywindow()
{
	// Get pointer to current active doc view
	CMDIChildWnd* pChild = reinterpret_cast<CMainFrame*>(m_pMainWnd)->MDIGetActive();
	if ( pChild == NULL )
	{
		AfxMessageBox( CString("NULL pChild") );
		return;
	}

	CString currentScript;
	CCMGfxView *pView = reinterpret_cast<CCMGfxView *>(pChild->GetActiveView());
	if ( pView != NULL )
	{
		// Get current script commands
		pView->GetWindowText( currentScript );
	}
	
	// Display the openGL dialog window with the current script
	CoglMFCDialogDlg openGLDlg;
	openGLDlg.SetScript( currentScript );
	InitSingletons();
	openGLDlg.DoModal();
	CleanUpSingletons();
}

void CCMGfxApp::InitSingletons()
{
	CRasterizer::Instance()->Initialize();
}

void CCMGfxApp::CleanUpSingletons()
{
}

void CCMGfxApp::DeleteSingletons()
{
	CRasterizer *pRasterizer = CRasterizer::Instance(); delete pRasterizer;
}


