// MMFBHVNode.h: interface for the MMFBHVNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFBHVNODE_H__BE632CD0_6A11_43C5_A547_0E6FDBDE010A__INCLUDED_)
#define AFX_MMFBHVNODE_H__BE632CD0_6A11_43C5_A547_0E6FDBDE010A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "MMFMathStructures.h"
//#include "MMFBHVObjectContainer.h"
class MMFBHVNode  
{
public:
	MMFBHVNode();
	virtual ~MMFBHVNode();
	int m_state;
	int m_attr;
	
	//MMFPoint3Di m_pos; //centre of node
	//MMFVector3Di m_radius;// radius of node
	int m_noObjects; //number of objects contained 
//	MMFBHVObjectContainer ** m_objects; //container objects for this node

	int m_numChildren; // number of child nodes

    MMFBHVNode ** m_children;



};

#endif // !defined(AFX_MMFBHVNODE_H__BE632CD0_6A11_43C5_A547_0E6FDBDE010A__INCLUDED_)
