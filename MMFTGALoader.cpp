// MMFTGALoader.cpp: implementation of the MMFTGALoader class.
//
//////////////////////////////////////////////////////////////////////

#include "MMFTGALoader.h"
#include <tchar.h>
///////////////////Defines used to determine if the file is comppressed///////////////
unsigned char UNCOMPRESSED_TGA[12] = {0,0,2,0,0,0,0,0,0,0,0,0};

unsigned char COMPRESSED_TGA[12] = {0,0,10,0,0,0,0,0,0,0,0,0};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MMFTGALoader::MMFTGALoader()
{

}

MMFTGALoader::~MMFTGALoader()
{

}


bool MMFTGALoader::LoadTGA(Texture * texture, LPTSTR filename){

	FILE * TGAFile; 
	//open the file 
	TGAFile = _tfopen(filename, "rb");

	//check file was loaded correctly

	if(TGAFile == NULL)
	{
	return false; //an error occurred 

	}

	//file was loaded correctly...

	//attemp to rad the file header

	if(fread(&m_tgaHeader, sizeof(TGAHeader),1,TGAFile) == 0)
	{

		return false; // return false if failed to read header
	}

	//header loaded correctly 

	//Check the header to see if the file is compressed or uncompreesed and call 
	//appropriate method

	if(memcmp(UNCOMPRESSED_TGA, &m_tgaHeader, sizeof(m_tgaHeader)) ==0)
	{
			// Load An Uncompressed TGA
		LoadUncompressedTGA(texture, TGAFile);


	}


	else if(memcmp(COMPRESSED_TGA, &m_tgaHeader, sizeof(m_tgaHeader)) ==0)
	{
		//MessageBox(NULL, "compressed file", "ERROR", MB_OK);
			// Load An Uncompressed TGA
		LoadCompressedTGA(texture,  TGAFile);


	}
	else
	{//the file header does not match either and there is an error or invalid file
MessageBox(NULL, "unsupported file", "ERROR", MB_OK);		// Display Error
		return false;
	}


return true;



}

bool  MMFTGALoader::LoadUncompressedTGA(Texture * texture, FILE * TGAFile)
{
	if(fread(m_tgaInfo.m_ucHeader, sizeof(m_tgaInfo.m_ucHeader),1,TGAFile) ==0)
	{
		return false; //error when reading from file
	}

	
	texture->m_uiWidth = m_tgaInfo.m_ucHeader[1] * 256 + m_tgaInfo.m_ucHeader[0]; //calculate width
	texture->m_uiHeight = m_tgaInfo.m_ucHeader[3] * 256 + m_tgaInfo.m_ucHeader[2]; //calculate height
	texture->m_uiBpp = m_tgaInfo.m_ucHeader[4]; //calculate bits per pixel
	m_tgaInfo.m_uiWidth = texture->m_uiWidth;
	m_tgaInfo.m_uiHeight = texture->m_uiHeight;
	m_tgaInfo.m_uiBpp = texture->m_uiBpp;


	//ensure all information is valid

	if((texture->m_uiWidth <=0) || (texture->m_uiHeight <=0) || ((texture->m_uiBpp !=24) && (texture->m_uiBpp!=32)))

	{

		return false; //info is not valid
	}

	if(texture->m_uiBpp ==24)
	{
		texture->muiType = GL_RGB;
	}
	else//if its not 24 bit then it must be 32 
	{
		texture->muiType = GL_RGBA;
	}

	//calulate bytes per pixel

	m_tgaInfo.m_uiBytespp = (m_tgaInfo.m_uiBpp/8); 

	//calculate memory needed to store image

	m_tgaInfo.m_uiImageSize = (m_tgaInfo.m_uiBytespp * m_tgaInfo.m_uiWidth * m_tgaInfo.m_uiHeight);

	
	
	//allocate memory

	texture->m_ucImageData =  new unsigned char[m_tgaInfo.m_uiImageSize];
	
	if(texture->m_ucImageData ==NULL)
	{

		return false; //memmory was not allocated properly
	}


	//attempt to read the image data 
	if (fread(texture->m_ucImageData, 1, m_tgaInfo.m_uiImageSize, TGAFile) != m_tgaInfo.m_uiImageSize)
	{

		return false; // reading image data failed
	}

	//ensure data is in RGB or RGBA data for opengl 
	FILE * ELOG;
	ELOG = fopen("elog.myf", "w");
	unsigned char list [1000000];
	//technique for swaping BGR to RGB by steve thomas
	for(unsigned int i = 0; i < (int) m_tgaInfo.m_uiImageSize; i += m_tgaInfo.m_uiBytespp)
	{
		//1st byte XOR 3rd BYte XOR 1st byte XOR 3rd byte
list[i] =  texture->m_ucImageData[i+3];
		texture->m_ucImageData[i] ^= texture->m_ucImageData[i +2] ^=
			texture->m_ucImageData[i] ^= texture->m_ucImageData[i+2];
	
	

	}
 fwrite((unsigned int *) list, sizeof( unsigned char ), (int) m_tgaInfo.m_uiImageSize, ELOG);
	fclose(TGAFile);
	fclose(ELOG);
	return true;  //file loaded sucessfully
	
	
	



}






bool  MMFTGALoader::LoadCompressedTGA(Texture * texture , FILE * TGAFile)
{


if(fread(m_tgaInfo.m_ucHeader, sizeof(m_tgaInfo.m_ucHeader),1,TGAFile) ==0)
	{
	MessageBox(NULL, "Could not read info header", "ERROR", MB_OK);		// Display Error
		return false; //error when reading from file
	}

	
	texture->m_uiWidth = m_tgaInfo.m_ucHeader[1] * 256 + m_tgaInfo.m_ucHeader[0]; //calculate width
	texture->m_uiHeight = m_tgaInfo.m_ucHeader[3] * 256 + m_tgaInfo.m_ucHeader[2]; //calculate height
	texture->m_uiBpp = m_tgaInfo.m_ucHeader[4]; //calculate bits per pixel
	m_tgaInfo.m_uiWidth = texture->m_uiWidth;
	m_tgaInfo.m_uiHeight = texture->m_uiHeight;
	m_tgaInfo.m_uiBpp = texture->m_uiBpp;


	//ensure all information is valid

	if((texture->m_uiWidth <=0) || (texture->m_uiHeight <=0) || ((texture->m_uiBpp !=24) && (texture->m_uiBpp!=32)))

	{
		MessageBox(NULL, "Invalid texture information", "ERROR", MB_OK);

		return false; //info is not valid
	}

	if(texture->m_uiBpp == 24)													// If the BPP of the image is 24...
		texture->muiType	= GL_RGB;											// Set Image type to GL_RGB
	else																	// Else if its 32 BPP
		texture->muiType	= GL_RGBA;	

	//calulate bytes per pixel

	m_tgaInfo.m_uiBytespp = (m_tgaInfo.m_uiBpp/8); 

	//calculate memory needed to store image

	m_tgaInfo.m_uiImageSize = (m_tgaInfo.m_uiBytespp * m_tgaInfo.m_uiWidth * m_tgaInfo.m_uiHeight);


	//allocate memory

	texture->m_ucImageData =  new unsigned char[m_tgaInfo.m_uiImageSize];
	
	if(texture->m_ucImageData ==NULL)
	{
		MessageBox(NULL, "Could not allocate memory for image", "ERROR", MB_OK);

		return false; //memmory was not allocated properly
	}

	unsigned int pixelCount = m_tgaInfo.m_uiHeight * m_tgaInfo.m_uiWidth;//no of pixels
	unsigned int currentPixel = 0;	//current pixel 
	unsigned int currentByte = 0;

	unsigned char * colourBuffer = new unsigned char[m_tgaInfo.m_uiBytespp];

//GLubyte * colourBuffer = (GLubyte *)malloc(m_tgaInfo.m_uiBytespp);
	do
	{
		unsigned char chunckHeader = 0;	//store the chunck header
		if(fread(&chunckHeader,sizeof(unsigned char),1,TGAFile)==0) //read header
		{
			MessageBox(NULL, "Could not read RLE header", "ERROR", MB_OK);
			return false; // reading of header failed;
		}


		if(chunckHeader <128)//if the chunck is a RAW chunck 
		{
			chunckHeader++; // add one to the value to get total number of raw pixels
		

			//pixel reading loop for current chunk
			//store colour values for pixel in colour buffer
			for(unsigned int counter = 0; counter < chunckHeader; counter++)
			{
				//read one pixel
				if(fread(colourBuffer,1,m_tgaInfo.m_uiBytespp,TGAFile) != m_tgaInfo.m_uiBytespp)
				{
					MessageBox(NULL, "Could not read image data", "ERROR", MB_OK);

					return false; //failed
				}

				//take colour values from colourbuffer BGR or BGRA and store in texture in RGB or RGBA format
			
				texture->m_ucImageData[currentByte] = colourBuffer[2]; //write the "R" byte
				texture->m_ucImageData[currentByte + 1] = colourBuffer[1]; //w/rite the "G" byte
				texture->m_ucImageData[currentByte + 2] = colourBuffer[0]; //write the "B" byte
			
				if(m_tgaInfo.m_uiBytespp ==4) //only write alph value if its a 32 bit image
				{
					texture->m_ucImageData[currentByte + 3] = colourBuffer[3];

				}

				//increment byte counter by no of bytes per pixel
				currentByte += m_tgaInfo.m_uiBytespp;
				currentPixel++;

			}


		}//if the chunck is a RAW chunck 
		else //it should be an RLE Header
		{
				chunckHeader -=127; //subtract 127  to get rid of the ID bit
			

				//read one pixel
				if(fread(colourBuffer,1,m_tgaInfo.m_uiBytespp,TGAFile) != m_tgaInfo.m_uiBytespp)
				{
					MessageBox(NULL, "Could not read from file", "ERROR", MB_OK);
					return false; //failed
				}


				//as its runlength encoded we need a loop to copythe 
				//pixel we just read multiple times 

				//the copy loop

				for(unsigned int counter = 0; counter <chunckHeader; counter ++)
				{


					//copy the "R" Byte
					texture->m_ucImageData[currentByte] = colourBuffer[2];
					//copy the "G" Byte
					texture->m_ucImageData[currentByte + 1] = colourBuffer[1];
					//copy the "B" Byte
					texture->m_ucImageData[currentByte + 2] = colourBuffer[0];

				if(m_tgaInfo.m_uiBytespp ==4) //only write alpha value if its a 32 bit image
				{
					texture->m_ucImageData[currentByte + 3] = colourBuffer[3];

				}
					//increment byte counter by no of bytes per pixel
				currentByte += m_tgaInfo.m_uiBytespp;
				currentPixel++;
				}



		}




	}while(currentPixel < pixelCount);

		fclose(TGAFile);



//free(colourBuffer);

	delete [] colourBuffer; //house keeping 
	return true;

}
