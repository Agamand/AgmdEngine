#ifndef _OCTREE_H_
#define _OCTREE_H_
/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine

status : incomming
============================================================================
*/


#define MAX_OCSPACE 8
namespace Agmd
{

	enum OcSpace
	{
		TOP_00,
		TOP_01,
		TOP_11,
		TOP_10,
		BOTTOM_00,
		BOTTOM_01,
		BOTTOM_11,
		BOTTOM_10
	};

	template <class T> class OcTree
	{
	public:
		OcTree();
		~OcTree(){}

	protected:
		
		OcTree* m_children[MAX_OCSPACE];
		T*		m_data
	};

	#include <Core/Tools/Octree.inl>

}

#endif /*	OCTREE_H	*/

