#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include <vector>

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
		
		QuadTree* m_children;
	};
}

#endif // !_QUADTREE_H_
