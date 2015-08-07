#include "stdafx.h"
#include "OpenGLControl.h"
#include ".\openglcontrol.h"

#include "Display/Rasterizer.h"


COpenGLControl::COpenGLControl(void)
{
}

COpenGLControl::~COpenGLControl(void)
{
}

BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

void COpenGLControl::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	ValidateRect(NULL);
}

void COpenGLControl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// OpenGL stuff
	if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED) return;

	// Map the OpenGL coordinates.
	glViewport(0, 0, cx, cy);

	// Projection view
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	// Set our current view orthographic
	glOrtho( 0, cx, cy, 0, 0, 1 );

	// Model view
	glMatrixMode(GL_MODELVIEW);

	// Resize OpenGL dialog
	if (GetSafeHwnd() != NULL)
	{
		CRect r;
		GetWindowRect( &r );
		ScreenToClient( &r );
		SetWindowPos( NULL, 0, 0, cx - 2 * r.left, cy - r.top - r.left, SWP_NOMOVE | SWP_NOZORDER );
	}
}

int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;

	oglInitialize();

	return 0;
}

void COpenGLControl::OnDraw(CDC *pDC)
{

}

void COpenGLControl::OnTimer(UINT nIDEvent)
{
	switch (nIDEvent)
	{
		case 1:
		{
			// Clear color buffer bit
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw OpenGL scene
			oglDrawScene();

			// Swap buffers
			SwapBuffers(hdc);

			break;
		}

		default:
			break;
	}

	CWnd::OnTimer(nIDEvent);
}

void COpenGLControl::OnMouseMove(UINT nFlags, CPoint point)
{
}

void COpenGLControl::oglCreate(CRect rect, CWnd *parent)
{
	CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_OWNDC, NULL, (HBRUSH)GetStockObject(BLACK_BRUSH), NULL);
	CString windowName("OpenGL");

	CreateEx(0, className, windowName, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, rect, parent, 0);

	hWnd = parent;
}

void COpenGLControl::oglInitialize(void)
{
	// Initial Setup:
	//
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32, // bit depth
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		16, // z-buffer depth
		0, 0, 0, 0, 0, 0, 0,
	};

	// Get device context only once.
	hdc = GetDC()->m_hDC;
	
	// Pixel format.
	m_nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, m_nPixelFormat, &pfd);

	// Create the OpenGL Rendering Context.
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);

	// Basic Setup:
	//
	// Set color to use when clearing the background.
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);

	glDisable( GL_DEPTH_TEST );

	// Send draw request
	OnDraw(NULL);
}

// Set command script
void COpenGLControl::oglSetScript( CString &script )
{
	m_ScriptParser.ParseScript( script );
}

// Draw graphics scene
void COpenGLControl::oglDrawScene(void)
{
	m_ScriptParser.ExecuteScript();
}
