// MMFStringlist.cpp: implementation of the MMFStringlist class.
//
//////////////////////////////////////////////////////////////////////

#include "MMFStringlist.h"
#include <fstream> 
#include <iostream>

using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MMFStringList::MMFStringList()
{
 
	first =NULL;
}

MMFStringList::~MMFStringList()
{

/*	if (first == NULL)
		return;
	StringItem * CurrentLink;
	StringItem * nextLink;
	CurrentLink = first;
	nextLink = first->next;*/
	
/*	while(CurrentLink != NULL){
		nextLink = CurrentLink->next;
		delete CurrentLink;
		CurrentLink = nextLink;
	}*/

}

void MMFStringList::add(char * string){

 StringItem * newItem = new StringItem;
 newItem->str = new char[strlen(string) -1];
 strcpy(newItem->str, string);
 newItem->next = first;
 first = newItem;
// char * strptr = new char[len + 1];
 //strcpy(ptr, string);

}


void MMFStringList::SaveTofile(char * fileName){

	StringItem * CurrentLink;
	StringItem * nextLink;

	ofstream outfile(fileName);
	CurrentLink = first;
	while(CurrentLink != NULL){
		for (int j=0; j< strlen(CurrentLink->str); j++)
		{
			outfile.put(CurrentLink->str[j]);
		}
	    outfile.put('\n');
		nextLink = CurrentLink->next;
		CurrentLink = nextLink;
	}
    outfile.close();
}



