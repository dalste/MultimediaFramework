// MMFButton.h: interface for the MMFButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFBUTTON_H__AABBC8BC_E975_41D8_B592_5DE4F15D4337__INCLUDED_)
#define AFX_MMFBUTTON_H__AABBC8BC_E975_41D8_B592_5DE4F15D4337__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MMFIElementFrame.h"
#include "MMFInterfaceElement.h"
#include "comUtil.h"
#include <tchar.h>
#include  "MMFXml.h"
#include "MMFMathStructures.h"

class MMFIElementButton: public MMFInterfaceElement
{
private: 
	int m_iStoredFrameCount;	//number of frames for button stored in xml page
	int m_iFrameCount; //actual frames in memory
	
	MMFIElementFrame ** m_frames; //pointer to frames
	
	int m_iCurrentFrame; //current frame

	int LoadButtonFrame(IXMLDOMNodePtr pNode);
public:
	
	MMFIElementButton(MMF_API_USED_TO_RENDER Api):  MMFInterfaceElement(Api), 
		m_frames(NULL), m_iFrameCount(0),m_iStoredFrameCount(0) {

	}



	virtual ~MMFIElementButton();
    virtual int LoadFromNode(IXMLDOMNodePtr pNode);
	virtual int LoadFramesFromNode(IXMLDOMNodePtr pNode);
	virtual int AddFrame(MMFIElementFrame * frame);

};

#endif // !defined(AFX_MMFBUTTON_H__AABBC8BC_E975_41D8_B592_5DE4F15D4337__INCLUDED_)
