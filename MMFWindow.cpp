// MMFWindow.cpp: implementation of the MMFWindow class.
//
//////////////////////////////////////////////////////////////////////

#include "MMFWindow.h"
#include "MMFAppManager.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
MMFAppManager Manager;
MMFWindow::MMFWindow()
{
	for (int i = 0; i<256; ++i){
		m_keys[i] = false;
	}
		
}

MMFWindow::~MMFWindow()
{

}



bool MMFWindow::Register(void) {
	LPCTSTR icon, cursor;
	HBRUSH brush;
	icon = MAKEINTRESOURCE(IDI_APPLICATION);
	cursor = MAKEINTRESOURCE(IDC_ARROW);
	brush = (HBRUSH) GetStockObject(WHITE_BRUSH);
	m_windowclass.lpszClassName = "windowclassname";
	m_windowclass.hInstance = Manager.GetInstance();
	m_windowclass.lpfnWndProc = WindowProc;
	m_windowclass.style = CS_HREDRAW|CS_VREDRAW;
	m_windowclass.lpszMenuName = NULL;
	m_windowclass.hIcon = LoadIcon(NULL, icon);
	m_windowclass.hCursor = LoadCursor(NULL,cursor);
	m_windowclass.hbrBackground = brush;
	m_windowclass.cbClsExtra = 0;
	m_windowclass.cbWndExtra = 4;


	if (!RegisterClass(&m_windowclass))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
	  return FALSE;
	}
	return true;

}

void MMFWindow::Unregister(void) {

		UnregisterClass(m_windowclass.lpszClassName,m_windowclass.hInstance );
}


void MMFWindow::Create(LPCTSTR title) {
	DWORD style = WS_OVERLAPPEDWINDOW;
	HMENU menu = NULL;
	HWND parent = NULL;
	LPVOID params = this;
	m_hWnd = CreateWindow("windowclassname", title, style, 0,0,1024,768, NULL,NULL,Manager.GetInstance(),params);
}
	// Dont Pass Anything To WM_CREATE



LRESULT MMFWindow::Destroy (HWND window, UINT message, WPARAM wparam, LPARAM lparam){

	PostQuitMessage(0);
	return 0;
}


void MMFWindow::Show (void) {
	ShowWindow(m_hWnd, SW_SHOW);
}


void MMFWindow::Resize(int width, int height){


}



HWND MMFWindow::getHWND(void){

return m_hWnd;

}

bool MMFWindow::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam){
bool messageHandled = false;
switch (msg) {
	case WM_SYSCOMMAND://intercept powersave/screensaver
	{ 
		switch(wParam) 
		{
		case SC_SCREENSAVE: 
		case SC_MONITORPOWER:
		messageHandled = true;
		}
		
	}
	break;
	case WM_KEYDOWN:	
		{
		KeyDown(wParam);
		messageHandled = true;
		}
			break;
	case WM_KEYUP: 
		{
		KeyUp(wParam);
		messageHandled = true;
		}
		break;
	}

return messageHandled;

}



void MMFWindow::KeyDown(WPARAM wParam){
	m_keys[wParam] = true;
}


void MMFWindow::KeyUp(WPARAM wParam){

	m_keys[wParam] = false;
}




