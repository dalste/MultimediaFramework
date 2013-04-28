// MMFOGLWindow.h: interface for the MMFOGLWindow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFOGLWINDOW_H__EF885F47_DA75_4121_86FD_CE8ADD0EAE30__INCLUDED_)
#define AFX_MMFOGLWINDOW_H__EF885F47_DA75_4121_86FD_CE8ADD0EAE30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MMFWindow.h"
#include "MMFAppManager.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library
#include "MMF3DSLoader.h"
#include "MMFTGALoader.h"

struct stSimpleCamera{
	float x, y, z;
	float yrot; 	

};

class MMFOGLWindow : public MMFWindow  
{

private:
	HGLRC m_hRC;
	HDC m_hDC;
	Texture *m_skyTex;
	bool m_bFullscreen;
	int m_iWidth;
	int m_iHeight;
	MMF3DSLoader loader;
	stSimpleCamera m_camera;
	MMFTGALoader m_tgaLoader;
protected:
	virtual LRESULT Destroy(HWND, UINT, WPARAM,LPARAM);
	friend LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM,LPARAM);
public:
	MMFOGLWindow() ;
	virtual ~MMFOGLWindow();
	bool virtual Register(void);
	bool Create(char* title, int bits,int width, int height, bool fullscreenflag);
	int InitGL(GLvoid);
	Show();
	GLvoid KillGLWindow(GLvoid);
	GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
	int DrawGLScene(GLvoid);
	void drawSky(void);
	virtual bool HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam);
	virtual void Resize(int width, int height);
	void doLogic(void);


};

#endif // !defined(AFX_MMFOGLWINDOW_H__EF885F47_DA75_4121_86FD_CE8ADD0EAE30__INCLUDED_)
