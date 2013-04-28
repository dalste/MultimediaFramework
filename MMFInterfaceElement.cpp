// MMFInterfaceElement.cpp: implementation of the MMFInterfaceElement class.
//
//////////////////////////////////////////////////////////////////////

#include "MMFInterfaceElement.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


MMFInterfaceElement::~MMFInterfaceElement()
{
	 if (m_name != NULL)
	 delete [] m_name  ;


	

}


int MMFInterfaceElement::LoadFromNode(IXMLDOMNodePtr pNode)
{
return 1;
}



bool MMFInterfaceElement::OnMouseDown(){
	return true;
}
bool MMFInterfaceElement::OnMouseUp(){
	return true;
}

bool MMFInterfaceElement::OnMouseDblClick(){
	return true;
}
bool MMFInterfaceElement::OnMouseDrag(){

return true;
}





