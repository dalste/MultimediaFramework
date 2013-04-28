// MMFApp.h: interface for the MMFApp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFAPP_H__A835F9F0_BCDB_4C59_8647_E296FA23910E__INCLUDED_)
#define AFX_MMFAPP_H__A835F9F0_BCDB_4C59_8647_E296FA23910E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <windows.h>
#include "MMFOGLWindow.h"
#include "timer.h"
#include "MMFStringList.h"
#include "MMFString.h"
#include "MMF3DObject.h"
#include  <typeinfo.h>
#include "MMF3DSLoader.h"
const MYMAXWINDOWS = 255;


class MMFApp  
{

private:
protected:
	bool m_bFirstTime;
	MMFOGLWindow window;
	MyTimer m_appTimer; // timer class
	MMFWindow window1;
	void addWindow(HWND hWnd);
	
public:
	MMFStringList list;
	MMFApp();
	~MMFApp();
    int Run(void);
	virtual void processAppLoop(void);

};

#endif // !defined(AFX_MMFAPP_H__A835F9F0_BCDB_4C59_8647_E296FA23910E__INCLUDED_)
