// MMFIElementFrame.h: interface for the MMFIElementFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFIELEMENTFRAME_H__39B9BB39_D33A_4E0A_82D3_75BD690743FA__INCLUDED_)
#define AFX_MMFIELEMENTFRAME_H__39B9BB39_D33A_4E0A_82D3_75BD690743FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MMFMathStructures.h"
#include "MMFXml.h"
#include "MMFInterfaceElement.h"

class MMFIElementFrame: public MMFInterfaceElement
{
private:
	LPTSTR m_Name;
	int m_iFrameNo;
	LPTSTR m_FileName;
public:
	MMFIElementFrame(MMF_API_USED_TO_RENDER Api): MMFInterfaceElement(Api) {
	}
	virtual ~MMFIElementFrame();
	virtual int LoadFromNode(IXMLDOMNodePtr Node);

};

#endif // !defined(AFX_MMFIELEMENTFRAME_H__39B9BB39_D33A_4E0A_82D3_75BD690743FA__INCLUDED_)
