// oglMFCDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CMGfx.h"
#include "oglMFCDialogDlg.h"
#include "Common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// oglMFCDialog message handlers


// CoglMFCDialogDlg dialog
CoglMFCDialogDlg::CoglMFCDialogDlg(CWnd* pParent /*=NULL*/) : CDialog(CoglMFCDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CoglMFCDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CoglMFCDialogDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CoglMFCDialogDlg message handlers
BOOL CoglMFCDialogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	/***************/
	/* ADDED CODE: */
	/***************/
	// Set default dialog size
	// Note: there is still some nonsense here because of the border width and the title bar
	MoveWindow( 10, 10, 
		WINDOW_WIDTH + ::GetSystemMetrics(SM_CXBORDER) * 2, 
		WINDOW_HEIGHT +  ::GetSystemMetrics(SM_CYCAPTION) + ::GetSystemMetrics(SM_CYBORDER) );
	// Resize OpenGL dialog
	if (GetDlgItem(IDC_OPENGL)->GetSafeHwnd() != NULL)
	{
		CRect r;
		GetDlgItem(IDC_OPENGL)->GetWindowRect( &r );
		GetDlgItem(IDC_OPENGL)->ScreenToClient( &r );
		GetDlgItem(IDC_OPENGL)->SetWindowPos( NULL, 0, 0,
			WINDOW_WIDTH, WINDOW_HEIGHT, SWP_NOMOVE | SWP_NOZORDER );
	}

	CRect rect;

	// Get size and position of the template textfield we created before in the dialog editor
	GetDlgItem(IDC_OPENGL)->GetWindowRect(rect);

	// Convert screen coordinates to client coordinates
	ScreenToClient(rect);

	// Create OpenGL Control window
	m_oglWindow.oglCreate(rect, this);

	// Setup the OpenGL Window's timer to render
	m_oglWindow.m_unpTimer = m_oglWindow.SetTimer(1, 40, 0);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CoglMFCDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CoglMFCDialogDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CoglMFCDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CoglMFCDialogDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	m_oglWindow.OnSize(nType, cx, cy);
}
