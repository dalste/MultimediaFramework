// MMFString.h: interface for the MMFString class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFSTRING_H__7043F43E_E67D_4261_9897_8DEDD4E8C260__INCLUDED_)
#define AFX_MMFSTRING_H__7043F43E_E67D_4261_9897_8DEDD4E8C260__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <tchar.h>
#include <windows.h>
class MMFString  
{
private:
	//LPTSTR pchar; // the string we encapsulate 
public:
	
	void extractFilePath(LPCTSTR str, LPTSTR result);
	void extractFileName(LPCTSTR str, LPTSTR result);
	void extracttFileExt(LPCTSTR str, LPTSTR result);

	MMFString();
	virtual ~MMFString();
//	getBstr(_bstr_t pBstr);


};

#endif // !defined(AFX_MMFSTRING_H__7043F43E_E67D_4261_9897_8DEDD4E8C260__INCLUDED_)
