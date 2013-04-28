// MMFButton.cpp: implementation of the MMFButton class.
//
//////////////////////////////////////////////////////////////////////
#include <cstring>
#include "MMFIElementButton.h"
#include <shlwapi.h>
#include <wchar.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



MMFIElementButton::~MMFIElementButton()
{

	
	 if (m_frames != NULL){

	  for(int i = 0; i < m_iFrameCount; i++){
	   delete m_frames[i];
	  }
	  	delete [] m_frames;
	 }

}

int MMFIElementButton::LoadFromNode(IXMLDOMNodePtr pNode)
{

	IXMLDOMNamedNodeMapPtr pNodeMap = NULL;
	IXMLDOMNodePtr pNodeItem = NULL;
	VARIANT varValue;
	char * tempStr;
	int tempInt;

	if (pNode ==NULL)
		return -1;

	pNodeMap = pNode->Getattributes();

	if (pNodeMap == NULL) 
		return -1;

	//get name
	varValue = GetNamedItemValue(pNodeMap, "Name");

	try {
	
	tempStr = _com_util::ConvertBSTRToString(_bstr_t(varValue));
	m_name = new TCHAR[_tcslen((tempStr)) + 1];
	_tcscpy(m_name, tempStr);
	m_name[_tcslen(m_name) ] = '\0'; 
	MessageBox(NULL,m_name,"hello", 1);
		
	//get FrameCount
	varValue = GetNamedItemValue(pNodeMap, "FrameCount");
	tempStr = _com_util::ConvertBSTRToString(_bstr_t(varValue));
	m_iStoredFrameCount = _ttoi(tempStr); 
	tempStr = "";
	tempStr = new char[255]; 
	sprintf(tempStr, "m_iStoredFrameCount= %i", m_iStoredFrameCount);
	MessageBox(NULL,tempStr ,"hello", 1);
    delete tempStr;

	//get x , y and z pos 
	//xPos
	varValue = GetNamedItemValue(pNodeMap, "XPos");
	tempStr = _com_util::ConvertBSTRToString(_bstr_t(varValue));
	 m_3iPosition.m_vals[0] = _ttoi(tempStr); 
	tempStr = "";
	tempStr = new char[255]; 
	sprintf(tempStr, "XPos= %i", m_3iPosition.m_vals[0]);
	MessageBox(NULL,tempStr ,"hello", 1);
    delete tempStr;
	//ypos
	varValue = GetNamedItemValue(pNodeMap, "YPos");
	tempStr = _com_util::ConvertBSTRToString(_bstr_t(varValue));
	m_3iPosition.m_vals[1] = _ttoi(tempStr); 
	tempStr = "";
	tempStr = new char[255]; 
	sprintf(tempStr, "YPos= %i", m_3iPosition.m_vals[1]);
	MessageBox(NULL,tempStr ,"hello", 1);
    delete tempStr;
	//zpos
	varValue = GetNamedItemValue(pNodeMap, "ZPos");
	tempStr = _com_util::ConvertBSTRToString(_bstr_t(varValue));
	m_3iPosition.m_vals[2] = _ttoi(tempStr); 
	tempStr = "";
	tempStr = new char[255]; 
	sprintf(tempStr, "ZPos= %i", m_3iPosition.m_vals[2]);

	MessageBox(NULL,tempStr ,"hello", 1);
    delete tempStr;


	//get visible 
	varValue = GetNamedItemValue(pNodeMap, "Visible");
	tempStr = _com_util::ConvertBSTRToString(_bstr_t(varValue));
	tempInt = _tcscmp(tempStr,"True"); 
	tempStr = "";
	tempStr = new char[255]; 

	if (tempInt ==0){
		m_isVisible = true;
		sprintf(tempStr, "Visible= %s","True" );
	}
	else
	{
		m_isVisible = false;
		sprintf(tempStr, "Visible= %s","False" );
	}
	
	
	MessageBox(NULL,tempStr ,"hello", 1);
    delete tempStr;
    

	LoadFramesFromNode(pNode);	

	 /*
	 if (pNodeItem != NULL) {
			pNodeItem->Release();
			pNodeItem = NULL;
		}
	 if (pNodeMap != NULL){
			pNodeMap->Release();
			pNodeMap = NULL;
	 }*/
	

	
	}
	catch(...) {

	}
return 1;
}


int MMFIElementButton::LoadFramesFromNode(IXMLDOMNodePtr pNode){

	IXMLDOMNodeListPtr pNodeList = NULL;
	IXMLDOMNodePtr plNodePtr = NULL;
	MMFIElementFrame * frame;
	_bstr_t TempStr;
	//select frames
	pNodeList = pNode->selectNodes("MMF-Button.Frame");

	if (pNodeList == NULL){

	return -1;	
	}
	
	//load frames 
	for (int i= 0;i < pNodeList->length;i++) {
		plNodePtr = pNodeList->Getitem(i);
		TempStr =plNodePtr->GetnodeName();
		if (_tcscmp((LPTSTR)TempStr, (LPTSTR)"MMF-Button.Frame" )==0){
			frame = new MMFIElementFrame(this->m_apiUsedToRender);
			frame->LoadFromNode(plNodePtr);
			AddFrame(frame);
	
		}


	}

return 1;
}




int MMFIElementButton::AddFrame(MMFIElementFrame * frame){

	if (frame == NULL) 
		return -1;

	MMFIElementFrame **tempPointer = new MMFIElementFrame*[m_iFrameCount + 1];
	//copy all pointers to new mem;
	for (int i = 0;i < m_iFrameCount; i++){
	tempPointer[i] = m_frames[i];
	}
	//delete old pointers 
	delete [] m_frames;
	m_frames = tempPointer; // point member to new pointers
	tempPointer = NULL; //for safety;
		//add to last position in new list
	++m_iFrameCount; //inc element count 
	m_frames[m_iFrameCount-1] =frame;
    
	
}