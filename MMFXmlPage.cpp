// MMFXmlPage.cpp: implementation of the MMFXmlPage class.
//
//////////////////////////////////////////////////////////////////////

#include "MMFXmlPage.h"
#include "MMFIElementButton.h"
#include <windows.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


MMFXmlPage::~MMFXmlPage() 
{
/*(	if (m_pPageNode) 
	m_pPageNode->Release();
	if(m_pPageNodeList)  
	m_pPageNodeList->Release();*/


	for (int i = 0; i < m_PageElementCount; i++)  
	{
		if (m_pPageElements[i] != NULL){
			
			delete (m_pPageElements[i]);
		}
	}

	delete [] m_pPageElements;	
	m_pPageElements = NULL;
}


int MMFXmlPage::LoadPage(){
	//long length;
	IXMLDOMNodePtr pNode=NULL;
	IXMLDOMNodePtr pNodeItem=NULL;
	IXMLDOMNodeListPtr pPageNodeList = NULL;
	IXMLDOMNamedNodeMapPtr pIXMLDOMNamedNodeMap = NULL;
//	VARIANT varValue;
	_bstr_t tempStr;

	if (m_pXMLDom == NULL)
		return -1; 	//exit if page not loaded 
	//load buttons	
	pPageNodeList = m_pXMLDom->selectNodes("//MMF-Screen/MMF-Button");
	
	if (pPageNodeList)
	for (int i = 0; i < pPageNodeList->length -1; i++ ) 
	{
	pNode = pPageNodeList->Getitem(i);
	if (pNode != NULL) 
	{
		tempStr = pNode->GetnodeName();
		if ( _tcsnccmp((LPTSTR) tempStr, (LPTSTR)"MMF-Button", 5) ==0){
			AddButtonElement(pNode);
		

		}

	}
	
}
return 1; 

}

void MMFXmlPage::getpageXML(char * XMLStr){
//	long length;
	IXMLDOMNodePtr pNode=NULL;
	IXMLDOMNodePtr pNodeItem=NULL;
	IXMLDOMNodeListPtr pPageNodeList = NULL;
	IXMLDOMNamedNodeMapPtr pIXMLDOMNamedNodeMap = NULL;
//	VARIANT varValue;
//	MMFIElementButton * button;

//pPageNode = m_pXMLDom->selectSingleNode("//MMF-Screen");
 ///pNode = m_pXMLDom->selectNodes("//MMF-Screen/MMF-Button[0]/MMF-Button.Frame[2]");


 

if (pPageNodeList)
for (int i = 0; i < pPageNodeList->length -1; i++ ) 
{
pNode = pPageNodeList->Getitem(i);
	if (pNode != NULL) 
	{
		//if (pNode->GetnodeName

	}
	
}


//m_pPageNodeList = m_pXMLDom->selectNodes("//MMF-Button[1]/");


/*m_pXMLDom->get_attributes( )
   
  printf("Results from selectNodes:\n");
   for (int i=0; i<m_pPageNodeList->length; i++)
   {
      pNode = pnl->item[i];
      printf("Node (%d), <%s>:\n\t%s\n", 
         i, (LPCSTR)pNode->nodeName, (LPCSTR)pnl->item[i]->xml);
   }*/

	//MessageBox(NULL, m_pXMLDom->xml,"hello", 1);
   //if (m_pPageNodeList)
//	m_pPageNodeList->get_length(&length);

//if (length){
//	m_pPageNodeList->get_item(0, &pNode);

//for(int i =0; i < length; i++){
	
 //if (length) 	m_pPageNodeList->get_item(i, &pNode); 

//if (pNode != NULL){
		//button->LoadFromNode(pNode);	
//}
/*	pIXMLDOMNamedNodeMap = (pNode)->Getattributes();
	if (pIXMLDOMNamedNodeMap !=NULL) 
	pNodeItem = pIXMLDOMNamedNodeMap->getNamedItem(_bstr_t("Name"));
	if (pNodeItem != NULL)
	varValue = pNodeItem->GetnodeValue();
	MessageBox(NULL,_bstr_t(varValue),"hello", 1);//}
	}
	 else
		 MessageBox(NULL,(LPCSTR)m_pXMLDom->parseError->Getreason(),"hello", 1);*/
//} 




}

int MMFXmlPage::AddButtonElement(IXMLDOMNodePtr node){
 
	if (node == NULL) 
		return -1;
	//create button 
	MMFIElementButton * newButton = new MMFIElementButton(this->m_apiUsedToRender);
	newButton->LoadFromNode(node);
	//newButton


	AddElement(newButton);

	return 1;
}

int MMFXmlPage::AddElement(MMFInterfaceElement * Element){

	if (Element == NULL) 
		return -1;

	MMFInterfaceElement **tempPointer = new MMFInterfaceElement*[m_PageElementCount + 1];
	//copy all pointers to new mem;
	for (int i = 0;i < m_PageElementCount; i++){
	tempPointer[i] = m_pPageElements[i];
	}
	//delete old pointers 
	delete [] m_pPageElements;
	m_pPageElements = tempPointer; // point member to new pointers
	tempPointer = NULL; //for safety;
		//add to last position in new list
	++m_PageElementCount; //inc element count 
	m_pPageElements[m_PageElementCount-1] =Element;
    
return 1;
}

//always use given pointer types rather than generic cpp pointers to the type as 
//you get some strange exceptions and memory acess violations if not 
