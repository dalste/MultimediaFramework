// MMFSceneNode.cpp: implementation of the MMFSceneNode class.
//
//////////////////////////////////////////////////////////////////////

#include "MMFSceneNode.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MMFSceneNode::MMFSceneNode()
{

}

MMFSceneNode::~MMFSceneNode()
{
	Destroy();
}


void MMFSceneNode::Destroy(){//iterate through all child nodes and release 

	for(std::list <MMFSceneNode*>::iterator i = m_children.begin(); i 
		!= m_children.end(); i++) 
	{
		(*i)->Release(); //release a node 
	}

	m_children.clear();//clear child list 

}


void MMFSceneNode::Update(void){//update node and all children


//iterate through all child nodes and update 
	for(std::list <MMFSceneNode*>::iterator i = m_children.begin(); i 
		!= m_children.end(); i++) 
	{
		(*i)->Update(); //update a node 
	}


}

void MMFSceneNode::Release(void){ 
	delete this;

}
void MMFSceneNode::AddChild(MMFSceneNode* pNode){

	m_children.push_back(pNode);
}

