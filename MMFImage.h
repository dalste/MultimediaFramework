// MMFImage.h: interface for the MMFImage class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_MMFIMAGE_H__84779515_EF50_47F1_872E_9034F7D23A35__INCLUDED_)
#define AFX_MMFIMAGE_H__84779515_EF50_47F1_872E_9034F7D23A35__INCLUDED_
//This class allows loading of TGA and bitmap formats into structures that 
//allow easy manipulation in both opengl and GDI for opengl 
#include <windows.h>
#include <stdio.h>
#include <gl\gl.h> // for OpenGL32 lib
#include <gl\glu.h> // for  GLu32 lib
#include <gl\glaux.h> //for GLaux lib

#include "MMFMathStructures.h"
#include "MMFUsefullEnumerations.h"
#include "MMFBitmapLoader.h"
#include  "MMFTgaLoader.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MMFImage  
{
private:
	LPTSTR m_fileName;
	MMFTGALoader m_tgaLoader;
	MMFBitmapLoader m_bitmapLoader;
protected:

	MMF_API_USED_TO_RENDER m_api;
	MMF_IMAGE_TYPE m_imageType;
	MMFPoint3Di m_pos3D;
	//MMFImageFileLoader * m_imageFileLoader;
	
	Texture * m_OGLImageData;  //image data stored here if OGL in use
	HBITMAP  m_WinImageData; //image data stored here if WIN in use
	HPALETTE  m_WinImagePallette;
	

	


public:
	MMFImage(MMF_API_USED_TO_RENDER api);
	int  LoadFromFile(LPTSTR ImageFileName);
	MMF_IMAGE_TYPE GetFileType(void);

	virtual ~MMFImage();

	int LoadBitmapToTexture(LPTSTR fileName, Texture* tex);
	int LoadTGAToTexture(LPTSTR  fileName, Texture* tex);
	int LoadTGAToHBitmap(LPTSTR  fileName, HBITMAP* pBmp,HPALETTE * pBmpPal);
	int LoadBitmapToHBitmap(LPTSTR  fileName, HBITMAP* pBmp,HPALETTE * pBmpPal);
	int Show(HWND window);

};

#endif // !defined(AFX_MMFIMAGE_H__84779515_EF50_47F1_872E_9034F7D23A35__INCLUDED_)
