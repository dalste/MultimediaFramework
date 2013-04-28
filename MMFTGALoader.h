// MMFTGALoader.h: interface for the MMFTGALoader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFTGALOADER_H__453D1721_D8D1_41BC_B6CA_F33EFDFD2BED__INCLUDED_)
#define AFX_MMFTGALOADER_H__453D1721_D8D1_41BC_B6CA_F33EFDFD2BED__INCLUDED_
//The source of this class is based on an article in Nehe's Open GL Tutorials 
//to see the code in its original form please see article : 
//Loading Compressed an Uncompressed Tga's by 
// Evan "terminate" Pipho.


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
	#include <windows.h>				// Standard Windows header
	#include <stdio.h>				// Standard Header For File I/O
	#include <gl\gl.h>				// Standard Header For OpenGL

struct Texture{

	unsigned char * m_ucImageData; //holds all the colour values for the image
	unsigned int m_uiBpp; // colour depth in bits per pixel (24 or 32)
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;
	unsigned int m_uiTexID;				// Texture ID For Use With glBindTexture.	
	unsigned int muiType;			 	// Data Stored In * ImageData (GL_RGB Or GL_RGBA)
	
	
	~Texture(){
		delete [] m_ucImageData;
	}

};

struct TGAHeader{
unsigned char m_ucHeader[12]; // file header to determine file type
};

struct TGAInfo{

	unsigned char m_ucHeader[6]; //holds the first 6 bytes of the file
	unsigned int m_uiBytespp; // colour depth in bytes per pixel (3 or 4)
	unsigned int m_uiImageSize;			// Amount Of Memory Needed To Hold The Image

	unsigned int  m_uiType;	 /// The Type Of Image, GL_RGB Or GL_RGBA
	unsigned int m_uiHeight;
	unsigned int m_uiWidth;
	unsigned int m_uiBpp; // colour depth in bits per pixel (24 or 32)


};



class MMFTGALoader  
{

private:
	TGAHeader m_tgaHeader; //used to store the file header 
	TGAInfo m_tgaInfo;		//used to store the file information
	bool LoadUncompressedTGA(Texture * , FILE *);
	bool LoadCompressedTGA(Texture * ,  FILE *);
public:
	MMFTGALoader();
	virtual ~MMFTGALoader();



	bool LoadTGA(Texture * texture, LPTSTR filename);

};

#endif // !defined(AFX_MMFTGALOADER_H__453D1721_D8D1_41BC_B6CA_F33EFDFD2BED__INCLUDED_)
