// MMFDebug.h: interface for the MMFDebug class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFDEBUG_H__F06633C7_E179_4335_8D10_1A52AD3F7D12__INCLUDED_)
#define AFX_MMFDEBUG_H__F06633C7_E179_4335_8D10_1A52AD3F7D12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <TCHAR.h>
#include <stdio.h>
#include <windows.h>


class MMFDebug  
{
private: 
	FILE * m_file;

public:
	MMFDebug(){
	
	}

	virtual ~MMFDebug(){

	}
	
	void PrintStr(LPTSTR str){
		m_file = NULL;
		 m_file = _tfopen("MMFDEBUG.txt", "a" );
		_ftprintf(m_file, "\n%s", str);
		if(m_file != NULL)
		fclose(m_file); 
	}
};

static MMFDebug g_debug;
#endif // !defined(AFX_MMFDEBUG_H__F06633C7_E179_4335_8D10_1A52AD3F7D12__INCLUDED_)
