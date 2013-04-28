// MMFImage.cpp: implementation of the MMFImage class.
//
//////////////////////////////////////////////////////////////////////

#include "MMFImage.h"
#include <tchar.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MMFImage::MMFImage(MMF_API_USED_TO_RENDER api)
{
	m_api = api;
//	m_imageFileLoader = NULL;
	m_pos3D.m_vals[0] = 0;
	m_pos3D.m_vals[1]  = 0;
	m_pos3D.m_vals[2]  = 0;
}

MMFImage::~MMFImage()
{
 //if (m_imageFileLoader != NULL)
//	 delete m_imageFileLoader;
}

int MMFImage::LoadFromFile(LPTSTR ImageFileName){
	//copy file name 
	m_fileName = new TCHAR[_tcslen(ImageFileName) + 1];
	_tcscpy(m_fileName, ImageFileName);
	m_imageType = GetFileType();
	
	if (m_imageType == MMF_BITMAP){//if bitmap then load for Current api 
		if (m_api == MMF_OGL) 
			LoadBitmapToTexture(ImageFileName, m_OGLImageData);

		if (m_api == MMF_WIN) 
			LoadBitmapToHBitmap(ImageFileName, &m_WinImageData, &m_WinImagePallette);
	}

	if (m_imageType == MMF_TGA){//if tga then load for Current api 
		if (m_api == MMF_OGL) 
			LoadTGAToTexture(ImageFileName, m_OGLImageData);

		if (m_api == MMF_WIN) 
			LoadTGAToHBitmap(ImageFileName, &m_WinImageData,&m_WinImagePallette);
	}

return 1;
}


MMF_IMAGE_TYPE MMFImage::GetFileType(){
	LPTSTR ext = new TCHAR[20];
	//fget file extension 
	_tsplitpath(m_fileName, NULL, NULL , NULL, ext);

	//get file type
	if (_tcsicmp(ext, ".bmp") == 0 ){
		delete [] ext;
		return MMF_BITMAP;
	}
		
	if (_tcsicmp(ext, ".tga") == 0 ){
		delete [] ext;
		return  MMF_TGA;
	}
return MMF_IMAGE_TYPE(-1);
}



int MMFImage::LoadBitmapToTexture(LPTSTR  fileName, Texture* tex){
	FILE * fp = NULL; //init file handle 	
	AUX_RGBImageRec *  pImageData;

	if (!fileName) 
		return -1; //invalid file name

	fp = _tfopen(fileName, "r");

	if(fp == NULL) 
		return -1; //file does not exist 

	//load image data and use temp pointer 
	pImageData = auxDIBImageLoad(fileName);

	//make member texture point to image data 
	tex->m_ucImageData = pImageData->data;
	tex->m_uiWidth = pImageData->sizeX;
	tex->m_uiHeight = pImageData->sizeY;
	tex->m_uiBpp = 24;
	tex->muiType = GL_RGB;
return 1;
}

	
int MMFImage::LoadTGAToTexture(LPTSTR  fileName, Texture* tex){
		m_tgaLoader.LoadTGA(tex, fileName);
	return 1;
}


int MMFImage::LoadTGAToHBitmap(LPTSTR  fileName, HBITMAP* pBmp,HPALETTE * pBmpPal){
	return 1;

}


int MMFImage::LoadBitmapToHBitmap(LPTSTR  fileName, HBITMAP* pBmp,HPALETTE * pBmpPal){

	m_bitmapLoader.LoadBMP(fileName, pBmp,pBmpPal); 

	return 1;

}


int MMFImage::Show(HWND window){
	//if(m_imageType != MMF_BITMAP)
	//	return -1;

	 PAINTSTRUCT   ps;
     HBITMAP       hBitmap, hOldBitmap;
     HPALETTE      hPalette, hOldPalette;
     HDC           hDC, hMemDC;
     BITMAP        bm;
	 LPTSTR szname =  m_fileName;
    hDC = BeginPaint(window , &ps );

   if( LoadBitmapToHBitmap(szname , &hBitmap, &hPalette ) )
   {
      GetObject( hBitmap, sizeof(BITMAP), &bm );
      hMemDC = CreateCompatibleDC( hDC );
      hOldBitmap = (HBITMAP)SelectObject( hMemDC, hBitmap );
      hOldPalette = SelectPalette( hDC, hPalette, FALSE );
      RealizePalette( hDC );

      BitBlt( hDC, 0, 0, bm.bmWidth, bm.bmHeight,
              hMemDC, 0, 0, SRCCOPY );

      SelectObject( hMemDC, hOldBitmap );
      DeleteObject( hBitmap );
      SelectPalette( hDC, hOldPalette, FALSE );
      DeleteObject( hPalette );
   }else
   {
	   MessageBox(window, "failed to show bitmap ",NULL,NULL);
   }
   EndPaint(window, &ps);

   return 1;

}

