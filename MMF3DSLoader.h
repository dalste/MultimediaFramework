// MMF3DSLoader.h: interface for the MMF3DSLoader class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMF3DSLOADER_H__D6A6ECC8_09FB_45CA_B5DA_AE1ED33EC2A0__INCLUDED_)
#define AFX_MMF3DSLOADER_H__D6A6ECC8_09FB_45CA_B5DA_AE1ED33EC2A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MMF3DObject.h"
#include <windows.h>
#include <stdio.h>
#include "MMFDebug.h"

extern MMFDebug g_debug;


class MMF3DSLoader  
{

private: 
	struct st3DSChunk{
		unsigned short m_ID;
		unsigned int m_length;
		unsigned int m_bytesRead;
		LPTSTR m_name;

		st3DSChunk(){
			m_name = NULL;
		}

		~st3DSChunk(){
			if (m_name != NULL)
			delete m_name;
		}
	};
	
	MMF3DObject **m_Objects;
	int m_ObjectCount;
	FILE *m_file;



	MMF3DObject * CreateObject(void);
	void ParseChunk(MMF3DObject* pObject, st3DSChunk *chunk); 
	int GetBinaryString(char*  pBuffer); 
	void SkipChunk(st3DSChunk * pChunk);
	LPTSTR GetChunkName(unsigned short ID);
	void ReadChunk(st3DSChunk * pChunk);
	void GetMeshObjectName(MMF3DObject* pObject, st3DSChunk *chunk);
	void GetMaterialName(MMF3DObject* pObject, st3DSChunk *chunk);
	void ReadMeshVertices(MMF3DObject* pObject, st3DSChunk *chunk);
	void ReadMeshFaces(MMF3DObject* pObject, st3DSChunk *chunk);
	void ReadMeshTexCoords(MMF3DObject* pObject, st3DSChunk *chunk);
	void ReadMeshMaterials(MMF3DObject* pObject, st3DSChunk *chunk);
	void GetDiffuseColour(MMF3DObject* pObject, st3DSChunk *chunk);
	void GetTexFileName(MMF3DObject* pObject, st3DSChunk *chunk);

	
public:
	MMF3DSLoader();
	virtual ~MMF3DSLoader();
	void LoadFile(LPTSTR fName);
	int RenderObject(int index);
};

#endif // !defined(AFX_MMF3DSLOADER_H__D6A6ECC8_09FB_45CA_B5DA_AE1ED33EC2A0__INCLUDED_)
