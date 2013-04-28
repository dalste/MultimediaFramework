// MMFWindow.h: interface for the MMFWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFWINDOW_H__1BA68487_221D_4E7C_867D_E9C567459CCE__INCLUDED_)
#define AFX_MMFWINDOW_H__1BA68487_221D_4E7C_867D_E9C567459CCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <windows.h>
#include "MMFInterfaceElement.h"
const MAX_INTERFACE_ELEMENTS = 255;
class MMFWindow  
{

private:
	

	
protected:
	friend LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM,LPARAM);
	WNDCLASS m_windowclass;
	HWND m_hWnd;
	MMFInterfaceElement * m_elements[MAX_INTERFACE_ELEMENTS];
	int m_windowWidth;
	int m_windowHeight;
	bool m_keys[256];

	virtual void Resize(int width, int height); //all derived classes must define this 
											//important for OGL windows gets called 
											//from WindowProc for WM_SIZE message
	virtual LRESULT Destroy(HWND, UINT, WPARAM,LPARAM);
	void KeyUp(WPARAM wParam);
	void KeyDown(WPARAM wParam);
public:
	MMFWindow();
	virtual ~MMFWindow();

	virtual void Create(LPCTSTR);

	virtual bool HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam); 
	virtual bool Register(void);
	 void Unregister(void);
	void Show(void);
	
	HWND getHWND(void);



};

#endif // !defined(AFX_MMFWINDOW_H__1BA68487_221D_4E7C_867D_E9C567459CCE__INCLUDED_)

