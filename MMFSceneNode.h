// MMFSceneNode.h: interface for the MMFSceneNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MMFSCENENODE_H__D1A078DA_0275_4DF7_AE53_8B5284743A6D__INCLUDED_)
#define AFX_MMFSCENENODE_H__D1A078DA_0275_4DF7_AE53_8B5284743A6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//nodes to implement
//geometry
//dof  
//rotation
//Scaling 
//translating
//animated dof
//switch 
//octtree for static objects in scene //impement this a a single node
//then we can use a terrrain node for terrain and the scene graph just holds 
//lights and dynamic objects 
#include <list>

class MMFSceneNode  
{
public:
	MMFSceneNode();
	virtual ~MMFSceneNode();//destroys all child nodes
	void Destroy();
	virtual void Update(void);//update node and all children
	//snsure to call base class update in child nodes
	void Release(void); //delete "this" node instance
	void AddChild(MMFSceneNode* pNode);

protected: 
std::list <MMFSceneNode*> m_children; //pointers to child nodes
	

};


/*

  class CDOFNode: public CSceneNode
{
public:
CDOFNode() { }
~CDOFNode() { }
void Initialize( float m[4][4] )
{
for( int i = 0; i < 4; i++ )
for( int j = 0; j < 4; j++ )
m_fvMatrix[i][j] = m[i][j];
}
void Update()
{
glPushMatrix();
glLoadMatrix( (float*)m_fvMatrix );
CSceneNode::Update();
glPopMatrix();
}
private:
float m_fvMatrix[4][4];
};
*/

#endif // !defined(AFX_MMFSCENENODE_H__D1A078DA_0275_4DF7_AE53_8B5284743A6D__INCLUDED_)
