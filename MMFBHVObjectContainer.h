// MMFBVHObjectContainer.h: interface for the MMFBVHObjectContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFBVHOBJECTCONTAINER_H__C69B6EA5_A201_4C91_935C_DFA6CE505DD4__INCLUDED_)
#define AFX_MMFBVHOBJECTCONTAINER_H__C69B6EA5_A201_4C91_935C_DFA6CE505DD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MMFBHVObjectContainer 
{//generic class to hold pointer to objects 
// for BHV tree  
public:
	int m_state;
	void * m_object; //pointer to the object we encapsula
	MMFBHVObjectContainer();
	virtual ~MMFBHVObjectContainer();

};

#endif // !defined(AFX_MMFBVHOBJECTCONTAINER_H__C69B6EA5_A201_4C91_935C_DFA6CE505DD4__INCLUDED_)
