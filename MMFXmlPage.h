// MMFXmlPage.h: interface for the MMFXmlPage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFXMLPAGE_H__F32754B6_491B_4525_8439_E39B03C4681F__INCLUDED_)
#define AFX_MMFXMLPAGE_H__F32754B6_491B_4525_8439_E39B03C4681F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MMFXml.h"
#include "MMFInterfaceElement.h"
#include <tchar.h>

class MMFXmlPage : public MMFXml  
{

private:
	MMF_API_USED_TO_RENDER m_apiUsedToRender;

	MMFInterfaceElement ** m_pPageElements;
	long m_PageElementCount;
	int AddElement(MMFInterfaceElement * Element);
	int AddButtonElement(IXMLDOMNodePtr node);

protected: 
		
public:
	MMFXmlPage(MMF_API_USED_TO_RENDER Api):m_apiUsedToRender(Api),m_pPageElements(NULL),
		 m_PageElementCount(0),MMFXml(){

	}
	
	virtual ~MMFXmlPage();
	int LoadPage();
	void getpageXML(char * XMLStr);
};

#endif // !defined(AFX_MMFXMLPAGE_H__F32754B6_491B_4525_8439_E39B03C4681F__INCLUDED_)
