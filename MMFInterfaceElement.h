// MMFInterfaceElement.h: interface for the MMFInterfaceElement class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFINTERFACEELEMENT_H__7CB70E38_57D2_4B0F_9B95_36E4123A8B5F__INCLUDED_)
#define AFX_MMFINTERFACEELEMENT_H__7CB70E38_57D2_4B0F_9B95_36E4123A8B5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MMFUsefullEnumerations.h"
#include "MMFMathStructures.h"
#include "MMFXml.h"

#import <msxml4.dll> 

using namespace MSXML2;	

class MMFInterfaceElement: public MMFXml
{
	
private:
	
	
protected:
	bool  m_active;// is the element active?
	

	MMFPoint3Di m_3iPosition; //holds x , y and z position 
	int m_iWidth;
	int m_iHeight;

	LPTSTR  m_name; //string of TCHAR
	bool m_isVisible;
	MMF_API_USED_TO_RENDER m_apiUsedToRender;

public:
	MMFInterfaceElement(MMF_API_USED_TO_RENDER Api):m_apiUsedToRender(Api),m_name(NULL){

	}
	virtual ~MMFInterfaceElement();


	bool initialise();
	bool GoToFrame(int frame);
	virtual bool OnMouseDown();
	virtual bool OnMouseUp();
	virtual bool OnMouseDblClick();
	virtual bool OnMouseDrag();
	virtual int LoadFromNode(IXMLDOMNodePtr pNode);



};

#endif // !defined(AFX_MMFINTERFACEELEMENT_H__7CB70E38_57D2_4B0F_9B95_36E4123A8B5F__INCLUDED_)
