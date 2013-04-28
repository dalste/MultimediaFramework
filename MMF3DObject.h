// MMF3DObject.h: interface for the MMF3DObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMF3DOBJECT_H__55FE3463_DAC9_47E2_B4A8_0336464C9BCF__INCLUDED_)
#define AFX_MMF3DOBJECT_H__55FE3463_DAC9_47E2_B4A8_0336464C9BCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MMFMathStructures.h"
#include <tchar.h>
#include <windows.h>
#include "MMFDebug.h"
#include "MMFmathLIB.h"


extern MMFDebug g_debug;

class MMF3DObjectMesh{
	public:	

		LPTSTR m_meshName;
		int m_vertCount;
		int m_numFaces;
		MMFVertice3Df * m_pVerts;
		MMFPoly3i * m_faces;
		MMFTextCoords2f * m_textCoords;
		MMFVector3Df *m_faceNormals;
		MMFVector3Df * m_vertNormals;

		void CreateVertexNormals(){
			int * numPolysShare = NULL;
			numPolysShare = new int[m_vertCount];
		
			for (unsigned int i = 0; i < (unsigned int) m_vertCount; ++i){
				numPolysShare[i] = 0;}

			m_vertNormals = new MMFVector3Df[m_vertCount]; 

			for(i = 0; i < (unsigned int) m_numFaces; i++) 
			{
				//increment poly references for each vertex 
				numPolysShare[m_faces[i].a] +=1;
				numPolysShare[m_faces[i].b] +=1;
				numPolysShare[m_faces[i].c] +=1;
				//add values of each face normal to vertex normal 

				m_vertNormals[m_faces[i].a].m_vals[0] += 
										m_faceNormals[i].m_vals[0];
				m_vertNormals[m_faces[i].a].m_vals[1] += 
										m_faceNormals[i].m_vals[1];
				m_vertNormals[m_faces[i].a].m_vals[2] += 
										m_faceNormals[i].m_vals[2];

				
				m_vertNormals[m_faces[i].b].m_vals[0] += 
										m_faceNormals[i].m_vals[0];
				m_vertNormals[m_faces[i].b].m_vals[1] += 
										m_faceNormals[i].m_vals[1];
				m_vertNormals[m_faces[i].b].m_vals[2] += 
										m_faceNormals[i].m_vals[2];

				
				m_vertNormals[m_faces[i].c].m_vals[0] += 
										m_faceNormals[i].m_vals[0];
				m_vertNormals[m_faces[i].c].m_vals[1] += 
										m_faceNormals[i].m_vals[1];
				m_vertNormals[m_faces[i].c].m_vals[2] += 
										m_faceNormals[i].m_vals[2];
			}
			//averaging
			for (i= 0; i <(unsigned int)m_vertCount; i ++){
			m_vertNormals[i].m_vals[0] /= numPolysShare[i];	
			m_vertNormals[i].m_vals[1] /= numPolysShare[i];	
			m_vertNormals[i].m_vals[2] /= numPolysShare[i];	
			MMFNormalise(m_vertNormals[i].m_vals);
			}

			//clean up
			if (numPolysShare != NULL) 
				delete[] numPolysShare;

		}

		MMF3DObjectMesh()
		{
			m_meshName = NULL;
			m_vertCount = 0;
			m_numFaces = 0;
			m_pVerts = NULL;
			m_faces = NULL;
			m_textCoords = NULL;
			m_vertNormals = NULL;
			m_faceNormals = NULL;
		}

		~MMF3DObjectMesh(){
			g_debug.PrintStr("Deleteing Object mesh");
			if (m_meshName !=NULL)
				delete [] m_meshName;
			if (m_pVerts != NULL) 
				delete []m_pVerts;
			if (m_faces != NULL)
				delete m_faces;
			if (m_textCoords !=NULL) 
				delete m_textCoords;
			if (m_vertNormals != NULL) 
				delete m_vertNormals;
			if ( m_faceNormals != NULL) 
				delete m_faceNormals;
		}

	};


class MMF3DObjectMaterial
{
public:
	LPTSTR m_name;
	MMFColour3Uc m_colour;
	LPTSTR m_textureFilename;

	MMF3DObjectMaterial(){
		m_name = NULL;
		m_textureFilename = NULL;
	}

	~MMF3DObjectMaterial(){
		if (m_name != NULL) 
			delete [] m_name;

		if (m_textureFilename != NULL) 
			delete [] m_textureFilename;
	}

};

class MMF3DObject  
{
public:

	
	//unrestricted access for speed 
	int m_meshCount;
	int m_materialCount;

	MMF3DObjectMesh ** m_meshList;
	MMF3DObjectMaterial ** m_materials;
	MMF3DObjectMesh * CreateMesh(void);
	MMF3DObjectMaterial * CreateMaterial(void);
	MMF3DObject();
	virtual ~MMF3DObject();

	void Render(void);

};





#endif // !defined(AFX_MMF3DOBJECT_H__55FE3463_DAC9_47E2_B4A8_0336464C9BCF__INCLUDED_)
