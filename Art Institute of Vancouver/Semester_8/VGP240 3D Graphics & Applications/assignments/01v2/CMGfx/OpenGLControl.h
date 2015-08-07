#pragma once
#include "afxwin.h"

#include <gl/gl.h>
#include <gl/glu.h>

#include "Commands/ScriptParser.h"

class COpenGLControl : public CWnd
{
	public:
		/******************/
		/* Public Members */
		/******************/
		UINT_PTR m_unpTimer;
		// View information variables

	private:
		/*******************/
		/* Private Members */
		/*******************/
		// Window information
		CWnd  *hWnd;
		HDC   hdc;			
		HGLRC hrc;			
		int   m_nPixelFormat;

		CScriptParser m_ScriptParser;

	public:
		COpenGLControl(void);
		virtual ~COpenGLControl(void);

		void oglCreate(CRect rect, CWnd *parent);
		void oglInitialize(void);
		void oglSetScript( CString &script );
		void oglDrawScene(void);

		// Added message classes:
		afx_msg void OnPaint();
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg	void OnDraw(CDC *pDC);
		afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnTimer(UINT nIDEvent);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);

		DECLARE_MESSAGE_MAP()
};