// MMFImageFileLoader.h: interface for the MMFImageFileLoader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFIMAGEFILELOADER_H__559D333D_4C7F_486C_84A3_3FA3D85EC184__INCLUDED_)
#define AFX_MMFIMAGEFILELOADER_H__559D333D_4C7F_486C_84A3_3FA3D85EC184__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>


class MMFBitmapLoader  
{
private:
	HBITMAP m_hBitmap ; //bitmap storage users of this class should load the bitmap into 
	
	BITMAP m_BitmapInfo;						//thier own structures
public:
	MMFBitmapLoader();
	virtual ~MMFBitmapLoader();
	bool LoadBMP(LPTSTR szFileName, HBITMAP *phBitmap,HPALETTE *phPalette );
	SetupBitmap (BOOL init);
	void ShowBitmap(HWND  window);
};

#endif // !defined(AFX_MMFIMAGEFILELOADER_H__559D333D_4C7F_486C_84A3_3FA3D85EC184__INCLUDED_)
