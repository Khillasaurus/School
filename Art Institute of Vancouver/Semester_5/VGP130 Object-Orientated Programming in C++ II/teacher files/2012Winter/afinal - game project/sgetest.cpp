// sgetest.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "sgetest.h"
//#include <Core/CApplication.h>
#include <SGE.h>

//int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR    lpCmdLine, int       nCmdShow)
//{
//	CApplication app;
//
//	app.Initialize("test", hInstance, 300,300);
//	app.Run();
//	app.Terminate();
//
//	return 0;
//}


void SGE_Initialize()
{
}
void SGE_Terminate()
{
}
bool SGE_Update(float fSeconds)
{
	//Quit Button
	if ( SGE::Input_IsKeyDown(SGE::Keys::ESCAPE))
	{
		return true;
	}
	return false;
}
void SGE_Render()
{
}
