// MMFAppManager.cpp: implementation of the MMFAppManager class.
//
//////////////////////////////////////////////////////////////////////

#include "MMFAppManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "MMFAppManager.h"
MMFAppManager::MMFAppManager()
{

}

MMFAppManager::~MMFAppManager()
{

}
void MMFAppManager::SetInstance(HINSTANCE instance){
	Instance = instance;
}


HINSTANCE MMFAppManager::GetInstance(void) const{
	return Instance;

}
