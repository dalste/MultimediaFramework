// MMF3DSLoader.cpp: implementation of the MMF3DSLoader class.
//
//////////////////////////////////////////////////////////////////////

#include "MMF3DSLoader.h"
#include "MMF3DSChunkDetails.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MMF3DSLoader::MMF3DSLoader()
{
	g_debug.PrintStr("MMF3DSLoader::MMF3DSLoader(): Creating 3DS Loader");
	m_ObjectCount = 0;
	m_Objects = NULL;
	m_file = NULL;
}

MMF3DSLoader::~MMF3DSLoader()
{
	g_debug.PrintStr("MMF3DSLoader::MMF3DSLoader(): Deleting 3DS Loader");
	g_debug.PrintStr("MMF3DSLoader::MMF3DSLoader(): Deleting objects");
	if (m_Objects  != NULL){
		for (int i = 0; i < m_ObjectCount; i++){
		delete m_Objects[i];
		}
		delete [] m_Objects;
	}
	g_debug.PrintStr("MMF3DSLoader::MMF3DSLoader(): Deleting object pointers");
	

}

void MMF3DSLoader::SkipChunk(MMF3DSLoader::st3DSChunk * pChunk){
		//output debug info 
	TCHAR buff[500];
	_stprintf(buff,"MMF3DSLoader::SkipChunk skipping chunck: %X:%s",
		pChunk->m_ID,pChunk->m_name);
	g_debug.PrintStr(buff); 

	int * buff2 = new int[pChunk->m_length];
	fread(buff2,1, pChunk->m_length - pChunk->m_bytesRead,m_file);
	delete [] buff2;
}

void MMF3DSLoader::ReadMeshVertices(MMF3DObject* pObject, 
									MMF3DSLoader::st3DSChunk *chunk)
{
	unsigned int numVerts = 0;

	chunk->m_bytesRead += (unsigned int) fread(&numVerts, 1, 2, m_file);
	//allocate memory 
	MMFVertice3Df * pVerts = new MMFVertice3Df[numVerts];
    float tempz;
	chunk->m_bytesRead += (unsigned int) fread( (void*)pVerts ,
		1, numVerts * sizeof(MMFVertice3Df), m_file);
	pObject->m_meshList[pObject->m_meshCount -1]->m_pVerts = pVerts;

	for (unsigned int i = 0; i < numVerts; i++){ 
	//swap coord for ogl
	tempz = pObject->m_meshList[pObject->m_meshCount -1]->m_pVerts[i].m_vals[2];
	pObject->m_meshList[pObject->m_meshCount -1]->m_pVerts[i].m_vals[2] = 
	-	pObject->m_meshList[pObject->m_meshCount -1]->m_pVerts[i].m_vals[1];
	pObject->m_meshList[pObject->m_meshCount -1]->m_pVerts[i].m_vals[1] =  tempz;
	}

	pObject->m_meshList[pObject->m_meshCount -1]->m_vertCount = numVerts;

	//output debug info 

	TCHAR buff[100];
	for(i = 0; i < numVerts; i++) {
		
	MMFVertice3Df * temp = &pObject->m_meshList[pObject->m_meshCount -1]->m_pVerts[i];
	_stprintf(buff,"vert no: %d: x = %f, y = %f, z = %f",i,temp->m_vals[0],temp->m_vals[1],
																	temp->m_vals[2]);
	g_debug.PrintStr(buff);

	}
	SkipChunk(chunk);
}

void MMF3DSLoader::ReadMeshFaces(MMF3DObject* pObject, 
								 MMF3DSLoader::st3DSChunk *chunk)
{
	
	g_debug.PrintStr("MMF3DSLoader::ReadMeshFaces: reading faces");
	unsigned int numFaces = 0;
	chunk->m_bytesRead += (unsigned int) fread(&numFaces, 1, 2 , m_file);

	struct stFaces{unsigned short p1, p2, p3, visibility;};
	stFaces  * pFaces = new stFaces[numFaces];

	chunk->m_bytesRead += (unsigned int) fread(pFaces, 1, 
						numFaces*sizeof(stFaces), m_file);

	MMF3DObjectMesh * pMesh= (pObject->m_meshList[pObject->m_meshCount -1 ]);

	pMesh->m_faces = new MMFPoly3i[numFaces];
	pMesh->m_faceNormals = new MMFVector3Df[numFaces];
	pMesh->m_numFaces = numFaces;
	TCHAR buff[100];
	float vert1[3]; //point a of poly 
	float vert2[3]; //point b of poly 
	float vert3[3]; //point c of poly 
	float vect1[3];//vector between vert 1 and 2 
	float vect2[3];//vector between vert 1 and 3
	float normal[3]; //normal between vect 1 and 2
	int tempIndex;
	for (unsigned int i=0; i < numFaces; ++i)
	{
	
		pMesh->m_faces[i].a = pFaces[i].p1; 
		pMesh->m_faces[i].b = pFaces[i].p2;
		pMesh->m_faces[i].c = pFaces[i].p3;
		//get two faces from mesh and calculate normals
		tempIndex = pMesh->m_faces[i].a; 
		vert1[0] = pMesh->m_pVerts[tempIndex].m_vals[0]; //x
		vert1[1] = pMesh->m_pVerts[tempIndex].m_vals[1]; //y
		vert1[2] = pMesh->m_pVerts[tempIndex].m_vals[2]; //z

		tempIndex = pMesh->m_faces[i].b; 
		vert2[0] = pMesh->m_pVerts[tempIndex].m_vals[0]; //x
		vert2[1] = pMesh->m_pVerts[tempIndex].m_vals[1]; //y
		vert2[2] = pMesh->m_pVerts[tempIndex].m_vals[2]; //z

		tempIndex = pMesh->m_faces[i].c; 
		vert3[0] = pMesh->m_pVerts[tempIndex].m_vals[0]; //x
		vert3[1] = pMesh->m_pVerts[tempIndex].m_vals[1]; //y
		vert3[2] = pMesh->m_pVerts[tempIndex].m_vals[2]; //z
		
		
		MMFSubtractVect3D(vert2, vert1, vect1); //get vectors from given points 
		MMFSubtractVect3D(vert3, vert1, vect2); 

		MMFCrossProduct(vect1, vect2, normal); ///calculate normal

		MMFNormalise(normal);
			
		//assign normal for this face
		pMesh->m_faceNormals[i].m_vals[0] = normal[0];
		pMesh->m_faceNormals[i].m_vals[1] = normal[1];
		pMesh->m_faceNormals[i].m_vals[2] = normal[2];

	_stprintf(buff,"face no: %d: a = %d, b = %d, c = %d;"     
        "     NORMAL: x=%f y=%f z=%f "
		,i,pFaces[i].p1,
		pFaces[i].p2,
	    pFaces[i].p3, normal[0], normal[1], normal[2]);



	g_debug.PrintStr(buff);
		
	}

	pMesh->CreateVertexNormals();
	delete []pFaces;

}

void MMF3DSLoader::ReadMeshTexCoords(MMF3DObject* pObject, 
									 MMF3DSLoader::st3DSChunk *chunk)
{

	g_debug.PrintStr("MMF3DSLoader::ReadMeshTexCoords: readin texures coordinates");
	unsigned short numVerts = 0;

	chunk->m_bytesRead += (unsigned int) fread(&numVerts, 1, 2, m_file);
	MMFTextCoords2f * pTexts = new MMFTextCoords2f[numVerts];

	chunk->m_bytesRead += (unsigned int) fread((void *)pTexts,1,
		numVerts*sizeof(MMFTextCoords2f), m_file);
	pObject->m_meshList[pObject->m_meshCount -1]->m_textCoords = pTexts;
	SkipChunk(chunk);

}
void MMF3DSLoader::ReadMeshMaterials(MMF3DObject* pObject, MMF3DSLoader::st3DSChunk *chunk){
    //determines which face references which material
	g_debug.PrintStr("MMF3DSLoader::ReadMeshMaterials reading material:");
	char str[256];	
	unsigned int charLen  =GetBinaryString(str);
	chunk->m_bytesRead += charLen;
	g_debug.PrintStr(str);
	unsigned short numFaces = 0;
	chunk->m_bytesRead += (unsigned int) fread(&numFaces,1,2,m_file);

	unsigned short * facesThisMaterialApplies = new unsigned short[numFaces];

	chunk->m_bytesRead += (unsigned int)fread(facesThisMaterialApplies, 1, 

                                                      numFaces*sizeof(unsigned short), m_file); 
	
	int MatID = 0;
	for( int i=0; i<pObject->m_materialCount; i++)
	{
		if( strcmp( str, pObject->m_materials[i]->m_name) == 0 )
			  MatID = i;
	}

	MMF3DObjectMesh* pMesh = (pObject->m_meshList[pObject->m_meshCount- 1]);
	for(int j=0; j<numFaces; j++)

	{
		int iIndex = facesThisMaterialApplies[j];
		pMesh->m_faces[j].matID = MatID;
	}

}

void MMF3DSLoader::ParseChunk(MMF3DObject* pObject, MMF3DSLoader::st3DSChunk *chunk){
	//output debug info 
	TCHAR buff[500];
	_stprintf(buff,"MMF3DSLoader::parseChunck(): procesing chunck: %X:%s",
		chunk->m_ID,chunk->m_name);
	g_debug.PrintStr(buff); 
	
	while(chunk->m_bytesRead < chunk->m_length)
	{
		MMF3DSLoader::st3DSChunk tempChunk;
		ReadChunk(&tempChunk);

		switch(tempChunk.m_ID){

			case EDIT3DS: //0x3D3D
				ParseChunk(pObject, &tempChunk);
			break;

			case MATERIAL:
				{
				pObject->CreateMaterial();
				//SkipChunk(&tempChunk);
				ParseChunk(pObject,&tempChunk);
				}
			break;
		    case MAT_NAME: 
                  GetMaterialName(pObject, &tempChunk);
				break;

			case MAT_DIFFUSE:  // Diffuse 
                  GetDiffuseColour(pObject,  &tempChunk);
                  break;

            case MAT_TEXMAP:  //if there's a texture wrapped to it 
                  ParseChunk(pObject, &tempChunk);
                  break;

			case MAT_TEXFLNM: // get filename of the texture
                  GetTexFileName(pObject, &tempChunk);
                  break;

			case NAMED_OBJECT:
				{
					pObject->CreateMesh();
					GetMeshObjectName(pObject,&tempChunk);
					ParseChunk(pObject, &tempChunk);	
				
				}
				break;

			case OBJ_MESH:
				ParseChunk(pObject, &tempChunk);
				break;

			case MESH_VERTICES:
				ReadMeshVertices(pObject, &tempChunk);
				break;
			case MESH_FACES: 
				{
					ReadMeshFaces(pObject, &tempChunk);
					ParseChunk(pObject, &tempChunk);
				}
				break;
			case MESH_TEX_VERT:
				ReadMeshTexCoords(pObject,&tempChunk);
				break;
			case MESH_MATER: 
				ReadMeshMaterials(pObject, &tempChunk);
				break;
			default: 
				SkipChunk(&tempChunk);
		}
		chunk->m_bytesRead += tempChunk.m_length;	
	}
}
	
void MMF3DSLoader::ReadChunk(MMF3DSLoader::st3DSChunk *pChunk)
{
	g_debug.PrintStr("MMF3DSLoader::ReadChunk: reading new chunk from file");
	unsigned short id = 0;
	unsigned int bytesRead = 0;
	unsigned int chunkLength = 0;

	bytesRead = (unsigned int)fread(&id, 1, 2, m_file);
	bytesRead += (unsigned int)fread(&chunkLength, 1, 4, m_file);
	pChunk->m_ID = id; 
	pChunk->m_length = chunkLength;
	pChunk->m_bytesRead = bytesRead;
	pChunk->m_name = GetChunkName(id);

	//debug info 
	LPTSTR buff = new TCHAR[_tcsclen("MMF3DSLoader::ReadChunk: read chunk: ") 
	  + _tcsclen(pChunk->m_name) + 3];
	_stprintf(buff, "%s %s", "MMF3DSLoader::ReadChunk: read chunk: ", pChunk->m_name);
	g_debug.PrintStr(buff);
	delete buff;
}



int MMF3DSLoader::GetBinaryString(char* pBuffer)
{

	if (m_file == NULL) 
		return -1;

      int index = 0;
      TCHAR buffer[100] = {0};

      fread(buffer, 1, 1, m_file);
      while( *(buffer + index++) != 0)
      {
            fread(buffer + index, 1, 1, m_file);
      }
	  *(buffer+index) = '\0';
      _tcscpy( pBuffer, buffer );

      return (int)(_tcsclen(buffer) + 1); //return bytes read
}

LPTSTR MMF3DSLoader::GetChunkName(unsigned short ID){
	g_debug.PrintStr("MMF3DSLoader::GetChunkName"); 
	LPTSTR buff = new TCHAR[100];
	switch(ID)
	{
		case PRIMARY:
			_tcscpy(buff, "PRIMARY");
			break;
		case EDIT3DS:
			_tcscpy(buff, "EDIT3DS");
			break;
		case KEYF3DS:
			_tcscpy(buff, "KEYF3DS");
			break;
		case VERSION:
			_tcscpy(buff, "VERSION");
			break;
		case MESH_VERSION:
			_tcscpy(buff, "MESH_VERSION");
			break;
		case KFVERSION:
			_tcscpy(buff, "KFVERSION");
			break;
		case COLOR_F:
			_tcscpy(buff, "COLOR_F");
			break;
		case COLOR_24:
			_tcscpy(buff, "COLOR_24");
			break;
		case LIN_COLOR_24:
			_tcscpy(buff, "LIN_COLOR_24");
			break;
		case LIN_COLOR_F:
			_tcscpy(buff, "LIN_COLOR_F");
			break;
		case INT_PERCENTAGE:
			_tcscpy(buff, "INT_PERCENTAGE");
			break;
		case FLOAT_PERC:
			_tcscpy(buff, "FLOAT_PERC");
			break;
		case MASTER_SCALE:
			_tcscpy(buff, "MASTER_SCALE");
			break;
		case IMAGE_FILE:
			_tcscpy(buff, "IMAGE_FILE");
			break;
		case AMBIENT_LIGHT:
			_tcscpy(buff, "AMBIENT_LIGHT");
			break;
		case NAMED_OBJECT:
			_tcscpy(buff, "NAMED_OBJECT");
			break;
		case OBJ_MESH:
			_tcscpy(buff, "OBJ_MESH");
			break;
		case MESH_VERTICES:
			_tcscpy(buff, "MESH_VERTICES");
			break;
		case VERTEX_FLAGS:
			_tcscpy(buff, "VERTEX_FLAGS");
			break;
		case MESH_FACES:
			_tcscpy(buff, "MESH_FACES");
			break;
		case MESH_MATER:
			_tcscpy(buff, "MESH_MATER");
			break;
		case MESH_TEX_VERT:
			_tcscpy(buff, "MESH_TEX_VERT");
			break;
		case MESH_XFMATRIX:
			_tcscpy(buff, "MESH_XFMATRIX");
			break;
		case MESH_COLOR_IND:
			_tcscpy(buff, "MESH_COLOR_IND");
			break;
		case MESH_TEX_INFO:
			_tcscpy(buff, "MESH_TEX_INFO");
			break;
		case HEIRARCHY:
			_tcscpy(buff, "HEIRARCHY");
			break;
		case MATERIAL:
			_tcscpy(buff, "MATERIAL");
			break;
		case MAT_NAME:
			_tcscpy(buff, "MAT_NAME");
			break;
		case MAT_AMBIENT:
			_tcscpy(buff, "MAT_AMBIENT");
			break;
		case MAT_DIFFUSE:
			_tcscpy(buff, "MAT_DIFFUSE");
			break;
		case MAT_SPECULAR:
			_tcscpy(buff, "MAT_SPECULAR");
			break;
		case MAT_SHININESS:
			_tcscpy(buff, "MAT_SHININESS");
			break;
		case MAT_FALLOFF:
			_tcscpy(buff, "MAT_FALLOFF");
			break;
		case MAT_EMISSIVE:
			_tcscpy(buff, "MAT_EMISSIVE");
			break;
		case MAT_SHADER:
			_tcscpy(buff, "MAT_SHADER");
			break;
		case MAT_TEXMAP:
			_tcscpy(buff, "MAT_TEXMAP");
			break;
		case MAT_TEXFLNM:
			_tcscpy(buff, "MAT_TEXFLNM");
			break;
		case OBJ_LIGHT:
			_tcscpy(buff, "OBJ_LIGHT");
			break;
		case OBJ_CAMERA:
			_tcscpy(buff, "OBJ_CAMERA");
			break;
		case ANIM_HEADER:
			_tcscpy(buff, "ANIM_HEADER");
			break;
		case ANIM_OBJ:
			_tcscpy(buff, "ANIM_OBJ");
			break;
		case ANIM_NAME:
			_tcscpy(buff, "ANIM_NAME");
			break;
		case ANIM_POS:
			_tcscpy(buff, "ANIM_POS");
			break;
		case ANIM_ROT:
			_tcscpy(buff, "ANIM_ROT");
			break;
		case ANIM_SCALE:
			_tcscpy(buff, "ANIM_SCALE");
			break;

		default: 
			_tcscpy(buff, "UNKNOWN");

	}
	return buff;
}

void MMF3DSLoader::GetMeshObjectName(MMF3DObject* pObject,
									 MMF3DSLoader::st3DSChunk *chunk)
{
	TCHAR strBuffer[512];
	unsigned int len = GetBinaryString(strBuffer);
	chunk->m_bytesRead += len;
	pObject->m_meshList[pObject->m_meshCount -1]->m_meshName = new TCHAR[_tcsclen(strBuffer) + 1];
	_tcscpy(pObject->m_meshList[pObject->m_meshCount -1]->m_meshName , (LPTSTR)strBuffer);

	LPTSTR buf = new TCHAR[_tcsclen("MMF3DSLoader::GetMeshObjectName: ") + 1 + _tcsclen( 
		pObject->m_meshList[pObject->m_meshCount -1]->m_meshName) + 1];
	_stprintf(buf, "%s%s","MMF3DSLoader::GetMeshObjectName: ", 
		pObject->m_meshList[pObject->m_meshCount -1]->m_meshName);
	g_debug.PrintStr(buf);
	delete [] buf;


}

void MMF3DSLoader::GetMaterialName(MMF3DObject* pObject,
									 MMF3DSLoader::st3DSChunk *chunk)

{

	TCHAR strBuffer[512];
	unsigned int len = GetBinaryString(strBuffer);
	chunk->m_bytesRead += len;
	pObject->m_materials[pObject->m_materialCount -1]->m_name= new TCHAR[_tcsclen(strBuffer) + 1];
	_tcscpy(pObject->m_materials[pObject->m_materialCount -1]->m_name, (LPTSTR)strBuffer);

	LPTSTR buf = new TCHAR[_tcsclen("MMF3DSLoader::GetMaterialName: ") + 1 + _tcsclen( 
		pObject->m_materials[pObject->m_materialCount -1]->m_name) + 1];
	_stprintf(buf, "%s%s","MMF3DSLoader::GetMaterialName: ", 
		pObject->m_materials[pObject->m_materialCount -1]->m_name);
	g_debug.PrintStr(buf);
	delete [] buf;

}

void MMF3DSLoader::GetTexFileName(MMF3DObject* pObject, MMF3DSLoader::st3DSChunk *chunk){
	
	TCHAR strBuffer[512];
	unsigned int len = GetBinaryString(strBuffer);
	chunk->m_bytesRead += len;
	pObject->m_materials[pObject->m_materialCount -1]->m_textureFilename= new TCHAR[_tcsclen(strBuffer) + 1];
	_tcscpy(pObject->m_materials[pObject->m_materialCount -1]->m_textureFilename, (LPTSTR)strBuffer);

	LPTSTR buf = new TCHAR[_tcsclen("MMF3DSLoader::GetTexFileName: ") + 1 + _tcsclen( 
		pObject->m_materials[pObject->m_materialCount -1]->m_textureFilename) + 1];
	_stprintf(buf, "%s%s","MMF3DSLoader::GetTexFileName: ", 
		pObject->m_materials[pObject->m_materialCount -1]->m_textureFilename);
	g_debug.PrintStr(buf);
	delete [] buf;

}
void MMF3DSLoader::GetDiffuseColour(MMF3DObject* pObject, MMF3DSLoader::st3DSChunk *chunk)
{

	struct tmpRGB{unsigned char r,g,b;};
	tmpRGB tempDiff;

	char chunkHeader[6];
	chunk->m_bytesRead += (unsigned int) fread(chunkHeader,1,6,m_file);
	chunk->m_bytesRead += (unsigned int) fread(&tempDiff,1,3,m_file);

	MMF3DObjectMaterial * pMat = (pObject->m_materials[pObject->m_materialCount -1]);

	pMat->m_colour.r = tempDiff.r;
	pMat->m_colour.g = tempDiff.g;
	pMat->m_colour.b = tempDiff.b;



	SkipChunk(chunk);

}

MMF3DObject * MMF3DSLoader::CreateObject(void){

	g_debug.PrintStr("MMF3DSLoader::CreateObject: creating new object");
	//create the object 
	MMF3DObject * ptempObj = new MMF3DObject;
	//create a copy of existing object array 
	MMF3DObject ** tempPpObjects  = new MMF3DObject*[m_ObjectCount + 1];
	//copy pointers into new array
	for (int i = 0; i <m_ObjectCount; ++i) 
		tempPpObjects[i] = m_Objects[i];

	// add new object 
	tempPpObjects[m_ObjectCount] = ptempObj;
	//increment object count 
	++m_ObjectCount;
	//point to newly created array 
	m_Objects = tempPpObjects;

	//return pointer to new object
	return tempPpObjects[m_ObjectCount -1];
}


void MMF3DSLoader::LoadFile(LPTSTR fName){
	//output debug info 
	int len = _tcsclen(fName) + _tcsclen("MMF3DSLoader::LoadFile: Loading file: ") + 2;
	LPTSTR buff = new TCHAR[len ];
	_stprintf(buff, "%s %s","MMF3DSLoader::LoadFile: Loading file: ",fName);
	g_debug.PrintStr(buff);
	delete [] buff;

	//open file 
	g_debug.PrintStr("MMF3DSLoader::LoadFile: Opening file in binary mode");
	if (m_file != NULL) 
		fclose(m_file);
	m_file = _tfopen(fName, "rb");

	if (m_file == NULL)
		return;


	//get initial chunk
	MMF3DSLoader::st3DSChunk chunk;
	ReadChunk( &chunk);
	//recurse into file
	MMF3DObject * obj1 = CreateObject();	
	ParseChunk(obj1,&chunk);
		

}

int MMF3DSLoader::RenderObject(int index){

	if(index > m_ObjectCount -1)
		return -1;

	m_Objects[index]->Render();

	return 1;
}
