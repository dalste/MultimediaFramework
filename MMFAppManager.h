// MMFAppManager.h: interface for the MMFAppManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFAPPMANAGER_H__F1FEE275_1713_4F68_BFF8_9DAA374ED53E__INCLUDED_)
#define AFX_MMFAPPMANAGER_H__F1FEE275_1713_4F68_BFF8_9DAA374ED53E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000




#include <windows.h>
const MAXWINDOWS =  10;

class MMFAppManager  
{
private:
	HINSTANCE Instance;
	
public:


	MMFAppManager();
	virtual ~MMFAppManager();
	void SetInstance(HINSTANCE);
	HINSTANCE GetInstance(void) const;

};


extern MMFAppManager Manager;

#endif // !defined(AFX_MMFAPPMANAGER_H__F1FEE275_1713_4F68_BFF8_9DAA374ED53E__INCLUDED_)
