// MMFXml.cpp: implementation of the MMFXml class.
//
//////////////////////////////////////////////////////////////////////

#include "MMFXml.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MMFXml::MMFXml()
{
	m_pXMLDom = NULL;
  // createXMLInstance();

}

MMFXml::~MMFXml()
{
	if (m_pXMLDom != NULL){
	m_pXMLDom.Release();
	m_pXMLDom = NULL;}
   
}


int MMFXml::createXMLInstance(void){
	if (m_pXMLDom){
	m_pXMLDom->Release();
	}
	m_pXMLDom = NULL;
	   m_hr= m_pXMLDom.CreateInstance(_uuidof(DOMDocument));
   if (FAILED(m_hr)) 
   {
      printf("Failed to instantiate an XML DOM.\n");
	  return -1;
   }

   return 1;
}


int MMFXml::loadXMLDoc( char * DocName){
 

	if (createXMLInstance() > 0) {

		m_pXMLDom->async = VARIANT_FALSE;
		if(m_pXMLDom->load(DocName)!=VARIANT_TRUE)
		{
			printf("Failed to load %s\n%s\n",*DocName,
			(LPCSTR)m_pXMLDom->parseError->Getreason());
			return -1;
		}
		else
		printf("XML DOM loaded from stocks.xml:\n%s\n", 
			(LPCSTR)m_pXMLDom->xml);

	}
	return 1;
}


VARIANT MMFXml::GetNamedItemValue(IXMLDOMNamedNodeMapPtr pNodeMap,
									  LPTSTR ItemName)
{
	IXMLDOMNodePtr pNodeItem = NULL;
	

	pNodeItem =  pNodeMap->getNamedItem(ItemName);

	if (pNodeItem != NULL) 
		return  pNodeItem->GetnodeValue();
	 
		
}