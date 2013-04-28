// MMFIElementFrame.cpp: implementation of the MMFIElementFrame class.
//
//////////////////////////////////////////////////////////////////////

#include "MMFIElementFrame.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
using namespace MSXML2;


MMFIElementFrame::~MMFIElementFrame()
{

}

int MMFIElementFrame::LoadFromNode(IXMLDOMNodePtr pNode){
	IXMLDOMNamedNodeMapPtr pNodeMap = NULL;
//	MMFIElementFrame * frame;
	VARIANT varValue;
	char * tempStr;
	
	
	pNodeMap = pNode->Getattributes();
	

	//get name 
	varValue = GetNamedItemValue(pNodeMap, "Name");
	tempStr = _com_util::ConvertBSTRToString(_bstr_t(varValue));
	m_name = new TCHAR[_tcslen((tempStr)) + 1];
	_tcscpy(m_name, tempStr);
	m_name[_tcslen(m_name) ] = '\0'; 
	MessageBox(NULL,m_name,"hello", 1);


	//get FrameNumber 
	varValue = GetNamedItemValue(pNodeMap, "Number");
	tempStr = _com_util::ConvertBSTRToString(_bstr_t(varValue));
	m_iFrameNo = _ttoi(tempStr); 
	tempStr = "";
	tempStr = new char[255]; 
	sprintf(tempStr, "m_iFrameNo= %i", m_iFrameNo);
	MessageBox(NULL,tempStr ,"hello", 1);
    delete tempStr;

	//get imageType
	varValue = GetNamedItemValue(pNodeMap, "Name");
	tempStr = _com_util::ConvertBSTRToString(_bstr_t(varValue));
	m_name = new TCHAR[_tcslen((tempStr)) + 1];
	_tcscpy(m_name, tempStr);
	m_name[_tcslen(m_name) ] = '\0'; 
	MessageBox(NULL,m_name,"hello", 1);



    delete tempStr;
	


	return 1;
}
