// MMFImageFileLoader.cpp: implementation of the MMFImageFileLoader class.
//
//////////////////////////////////////////////////////////////////////

#include "MMFBitmapLoader.h"

#include "MMFAppManager.h"
#include"resource.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MMFBitmapLoader::MMFBitmapLoader()
{

}

MMFBitmapLoader::~MMFBitmapLoader()
{
DeleteObject (m_hBitmap);
}

bool MMFBitmapLoader::LoadBMP(LPTSTR szFileName, HBITMAP *phBitmap,HPALETTE *phPalette )
{ 
BITMAP  bm;

   *phBitmap = NULL;
   *phPalette = NULL;

   // Use LoadImage() to get the image loaded into a DIBSection
   *phBitmap = (HBITMAP)LoadImage( NULL, szFileName, IMAGE_BITMAP, 0, 0,
               LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
   if( *phBitmap == NULL )
     return FALSE;

   // Get the color depth of the DIBSection
   GetObject(*phBitmap, sizeof(BITMAP), &bm );
   // If the DIBSection is 256 color or less, it has a color table
   if( ( bm.bmBitsPixel * bm.bmPlanes ) <= 8 )
   {
   HDC           hMemDC;
   HBITMAP       hOldBitmap;
   RGBQUAD       rgb[256];
   LPLOGPALETTE  pLogPal;
   WORD          i;

   // Create a memory DC and select the DIBSection into it
   hMemDC = CreateCompatibleDC( NULL );
   hOldBitmap = (HBITMAP)SelectObject( hMemDC, *phBitmap );
   // Get the DIBSection's color table
   GetDIBColorTable( hMemDC, 0, 256, rgb );
   // Create a palette from the color table
   pLogPal = (LOGPALETTE *)malloc( sizeof(LOGPALETTE) + (256*sizeof(PALETTEENTRY)) );
   pLogPal->palVersion = 0x300;
   pLogPal->palNumEntries = 256;
   for(i=0;i<256;i++)
   {
     pLogPal->palPalEntry[i].peRed = rgb[i].rgbRed;
     pLogPal->palPalEntry[i].peGreen = rgb[i].rgbGreen;
     pLogPal->palPalEntry[i].peBlue = rgb[i].rgbBlue;
     pLogPal->palPalEntry[i].peFlags = 0;
   }
   *phPalette = CreatePalette( pLogPal );
   // Clean up
   free( pLogPal );
   SelectObject( hMemDC, hOldBitmap );
   DeleteDC( hMemDC );
   }
   else   // It has no color table, so use a halftone palette
   /*{
   HDC    hRefDC;

   hRefDC = GetDC( NULL );
   *phPalette = CreateHalftonePalette( hRefDC );
   ReleaseDC( NULL, hRefDC );
   }*/
   return TRUE;

   }
MMFBitmapLoader::SetupBitmap (BOOL init){

	if(init) {
		 m_hBitmap = LoadBitmap (Manager.GetInstance(), MAKEINTRESOURCE(IDB_BITMAP));
	
		GetObject(m_hBitmap, sizeof(m_BitmapInfo), &m_BitmapInfo);
	}

	else 
		DeleteObject(m_hBitmap);
}


void MMFBitmapLoader::ShowBitmap(HWND window){

PAINTSTRUCT   ps;
     HBITMAP       hBitmap, hOldBitmap;
     HPALETTE      hPalette, hOldPalette;
     HDC           hDC, hMemDC;
     BITMAP        bm;
	LPTSTR szname =  "bitmap2.BMP";
   hDC = BeginPaint(window , &ps );

   if( LoadBMP(szname , &hBitmap, &hPalette ) )
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

}