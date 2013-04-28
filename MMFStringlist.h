// MMFStringlist.h: interface for the MMFStringlist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFSTRINGLIST_H__D212609C_24BF_4ED3_9B40_085E01C1FF04__INCLUDED_)
#define AFX_MMFSTRINGLIST_H__D212609C_24BF_4ED3_9B40_085E01C1FF04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <vector>
#include <cstring>
class StringItem 
{
public:
	char * str;
	StringItem * next;
	StringItem(){
		next = NULL;
	}


	~StringItem(){
     delete [] str;
	}
};


class MMFStringList  
{
private: 

 StringItem * first;
 int m_count; 
public:
	MMFStringList();
	virtual ~MMFStringList();
	void add(char * string);

	void SaveTofile(char * fileName);

};

#endif // !defined(AFX_MMFSTRINGLIST_H__D212609C_24BF_4ED3_9B40_085E01C1FF04__INCLUDED_)
