// MMFXml.h: interface for the MMFXml class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFXML_H__2C59A7AD_D323_4FC4_9B61_C7BE1838E216__INCLUDED_)
#define AFX_MMFXML_H__2C59A7AD_D323_4FC4_9B61_C7BE1838E216__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include "comUtil.h"
#include <tchar.h>

#import <msxml4.dll> 

using namespace MSXML2;

class MMFXml  
{

private:
	int createXMLInstance(void);
protected:
	IXMLDOMDocument2Ptr m_pXMLDom;
	HRESULT m_hr;
public:
	
	MMFXml();
	virtual ~MMFXml();
	int loadXMLDoc( char* DocName );
	VARIANT GetNamedItemValue(IXMLDOMNamedNodeMapPtr pNodeMap,
	LPTSTR ItemName);

};

#endif // !defined(AFX_MMFXML_H__2C59A7AD_D323_4FC4_9B61_C7BE1838E216__INCLUDED_)
