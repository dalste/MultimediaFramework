// MMF3DObject.cpp: implementation of the MMF3DObject class.
//
//////////////////////////////////////////////////////////////////////

#include "MMF3DObject.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



  
MMF3DObject::MMF3DObject()
{
	g_debug.PrintStr("MMF3DObject::MMF3DObject(): Creating 3d object");
	m_meshList = NULL;
	m_meshCount = 0;
	m_materialCount = 0;
	m_materials = NULL;
}

MMF3DObject::~MMF3DObject()
{
	 g_debug.PrintStr("MMF3DObject::~MMF3DObject(): Deleting 3d object");

	 if (m_meshList != NULL){ //delete object meshes 
		 for(int i = 0; i < m_meshCount; i++){
			delete m_meshList[i];
		 }

		 delete [] m_meshList; //delete pointers to meshes
	 }
	 
	 if (m_materials != NULL){ //delete object materials 
		 for(int i = 0; i < m_materialCount; i++){
			delete m_materials[i];
		 }

		 delete [] m_materials; //delete pointers to meshes
	 }
		

}

MMF3DObjectMesh * MMF3DObject::CreateMesh(void){

	g_debug.PrintStr("MMF3DObject::CreateMesh creating new object mesh");
	//create the mesh
	MMF3DObjectMesh * ptempMesh = new MMF3DObjectMesh;
	//create a copy of existing object array 
	MMF3DObjectMesh ** tempPpMeshes  = new MMF3DObjectMesh* [m_meshCount + 1];
	//copy pointers into new array
	for (int i = 0; i <m_meshCount; ++i) 
		tempPpMeshes[i] = m_meshList[i];

	// add new mesh 
	tempPpMeshes[m_meshCount] = ptempMesh;
	//increment object count 
	++m_meshCount;
	//point to newly created array 
	m_meshList = tempPpMeshes;

	//return pointer to new mesh
	return tempPpMeshes[m_meshCount -1];
}
MMF3DObjectMaterial * MMF3DObject::CreateMaterial(void){


	g_debug.PrintStr("MMF3DObject::CreateMaterial creating new object material");
	//create the material 
	MMF3DObjectMaterial * ptempMat= new MMF3DObjectMaterial;
	//create a copy of existing material array 
	MMF3DObjectMaterial ** tempPpMaterials  = new MMF3DObjectMaterial* [m_materialCount + 1];
	//copy pointers into new array
	for (int i = 0; i <m_materialCount; ++i) 
		tempPpMaterials[i] = m_materials[i];

	// add new material 
	tempPpMaterials[m_materialCount] = ptempMat;
	//increment material count 
	++m_materialCount;
	//point to newly created array 
	m_materials = tempPpMaterials;

	//return pointer to new material
	return tempPpMaterials[m_materialCount -1];
}

void MMF3DObject::Render(void){

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	for(int i=0; i < m_meshCount; ++i) //for eacch mesh 
	{
	
		for (int j=0; j< m_meshList[i]->m_numFaces; ++j){
			if (m_materialCount > 0) 
			if((int)m_meshList[i]->m_faces[j].matID < m_materialCount) 
			//glColor3ub(m_materials[m_meshList[i]->m_faces[j].matID]->m_colour.r ,
					//	m_materials[m_meshList[i]->m_faces[j].matID]->m_colour.g, 
			//	m_materials[m_meshList[i]->m_faces[j].matID]->m_colour.b );
				
			glBegin(GL_TRIANGLES);
			glColor3f(0.0f,0.0f,0.5f);
			glNormal3f(m_meshList[i]->m_vertNormals[ m_meshList[i]->m_faces[j].a].m_vals[0],
				m_meshList[i]->m_vertNormals[ m_meshList[i]->m_faces[j].a].m_vals[1],
				m_meshList[i]->m_vertNormals[ m_meshList[i]->m_faces[j].a].m_vals[2]
				);

			glVertex3f(
				m_meshList[i]->m_pVerts[m_meshList[i]->m_faces[j].a].m_vals[0],
				m_meshList[i]->m_pVerts[m_meshList[i]->m_faces[j].a].m_vals[1],
				m_meshList[i]->m_pVerts[m_meshList[i]->m_faces[j].a].m_vals[2]);
				
			glNormal3f(m_meshList[i]->m_vertNormals[ m_meshList[i]->m_faces[j].b].m_vals[0],
				m_meshList[i]->m_vertNormals[ m_meshList[i]->m_faces[j].b].m_vals[1],
				m_meshList[i]->m_vertNormals[ m_meshList[i]->m_faces[j].b].m_vals[2]
				);	
			glVertex3f(
				m_meshList[i]->m_pVerts[m_meshList[i]->m_faces[j].b].m_vals[0],
				m_meshList[i]->m_pVerts[m_meshList[i]->m_faces[j].b].m_vals[1],
				m_meshList[i]->m_pVerts[m_meshList[i]->m_faces[j].b].m_vals[2]);

			glNormal3f(m_meshList[i]->m_vertNormals[ m_meshList[i]->m_faces[j].c].m_vals[0],
				m_meshList[i]->m_vertNormals[ m_meshList[i]->m_faces[j].c].m_vals[1],
				m_meshList[i]->m_vertNormals[ m_meshList[i]->m_faces[j].c].m_vals[2]
				);	

			glVertex3f(
				m_meshList[i]->m_pVerts[m_meshList[i]->m_faces[j].c].m_vals[0],
				m_meshList[i]->m_pVerts[m_meshList[i]->m_faces[j].c].m_vals[1],
				m_meshList[i]->m_pVerts[m_meshList[i]->m_faces[j].c].m_vals[2]);
			
			glEnd();

		}

	}


}
