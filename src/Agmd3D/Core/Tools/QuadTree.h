#ifndef _QUADTREE_H_
#define _QUADTREE_H_

/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine

status : abandon
============================================================================
*/


#define MAX_QUADFACE 4
namespace Agmd
{

	enum QuadFace
	{
		TOP,
		LEFT,
		BOTTOM,
		RIGHT
	};

	struct QuadTree
	{
	public:
		QuadTree();
		~QuadTree();

	protected:
		
		QuadTree* m_children[MAX_QUADFACE];
	};
}

#endif // !_QUADTREE_H_
