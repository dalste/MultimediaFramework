// MMFString.cpp: implementation of the MMFString class.
//
//////////////////////////////////////////////////////////////////////

#include "MMFString.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MMFString::MMFString()
{

}

MMFString::~MMFString()
{

}


void MMFString::extractFileName(LPCTSTR str, LPTSTR result){//assumes buffer already allocated


	if (str == NULL) 
		return;
	if (result == NULL) 
		return;

	int length;
	int fileNameStartIndex;
	//LPTSTR tempStr;
	
	LPTSTR pdest;
	length = _tcslen (str);
	pdest = _tcsrchr( str, '\\'); //pdet points to last "\"
	fileNameStartIndex = (int)(pdest - str + 1); //get index 
	fileNameStartIndex; //advance to next char

	fileNameStartIndex;
	//copy to new location 
	int j = 0;
	for (int i = fileNameStartIndex; i < length; ++i) {
		result[j] = str[i];
		++j;
	}
	result[j] = '\0';


	

}
void MMFString::extractFilePath(LPCTSTR str, LPTSTR result){
	//int length;
//	int fileNameStartIndex;
//	LPTSTR tempStr;

}
void MMFString::extracttFileExt(LPCTSTR str, LPTSTR result){
//	int length;
//	int fileNameStartIndex;
//	LPTSTR tempStr;

}