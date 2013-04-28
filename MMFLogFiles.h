// MMFLogFiles.h: interface for the MMFLogFiles class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFLOGFILES_H__0305DDDE_7DD5_4957_84A6_F6B97167C6FC__INCLUDED_)
#define AFX_MMFLOGFILES_H__0305DDDE_7DD5_4957_84A6_F6B97167C6FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include  "MMFStringList.h"
char * LOG_FILE_NAME;

class MMFLogFiles  
{
private:
	char * LogFilenName;
public:
	MMFLogFiles();
	virtual ~MMFLogFiles();

};

#endif // !defined(AFX_MMFLOGFILES_H__0305DDDE_7DD5_4957_84A6_F6B97167C6FC__INCLUDED_)
