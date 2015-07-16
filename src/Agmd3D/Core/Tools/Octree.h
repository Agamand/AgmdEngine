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

#include <vector>
#include <stack>
#include <map>
#include <Core/Tools/BoundingBox.h>
#include <Utilities/Util.h>


using namespace AgmdUtilities;

#define MAX_OCSPACE 8
#define OCTREE_POOL_SIZE 10000
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

	static vec3 translateTable[] = {
		vec3(-1,1,-1),
		vec3(-1,1,1),
		vec3(1,1,1),
		vec3(1,1,-1),
		vec3(-1,-1,-1),
		vec3(-1,-1,1),
		vec3(1,-1,1),
		vec3(1,-1,-1),

	};



	static void BboxFrom(const BoundingBox& base,BoundingBox& out,a_uint32 subspace)
	{
		vec3 translation = translateTable[subspace];
		out = base/2.f;
		out += translation*(out.GetMax()-out.GetCenter());
	}

	static void ReverseBboxFrom(const BoundingBox& from,BoundingBox& out,a_uint32 subspace)
	{
		vec3 translation = translateTable[subspace];
		out = from;
		out += -translation*(from.GetMax()-from.GetCenter());
		out = out*2.f;
	}


	static a_uint8 GetBboxForParent(const BoundingBox& from,BoundingBox& out,vec3 direction)
	{
		a_uint8 sub = direction.y >= 0 ? 4 : 0;
		if(direction.x < 0 && direction.z >= 0)
			sub +=3;
		else if(direction.x < 0 && direction.z < 0)
			sub +=2;
		else if(direction.x >= 0 && direction.z < 0)
			sub +=1;

		vec3 translation = translateTable[sub];
		out = from;
		out += -translation*(from.GetMax()-from.GetCenter());
		out = out*2.f;
		return sub;
	}

	template <class T> class OcTreeMgr;

	template <class T> class OcTree
	{
		
	public:
		friend class OcTreeMgr<T>;
		OcTree();

		OcTree(OcTreeMgr<T>* mgr,BoundingBox& bbox);
		~OcTree(){};
		void Remove(T* data)
		{
			for(a_uint32 i = 0,len = m_data.size(); i < len; i++)
			{
				if(m_data[i] == data)
				{
				
					m_data.erase(m_data.begin()+i);
					break;
				}
			}
		}
	//protected:
		
		OcTree<T>*		m_children[MAX_OCSPACE];
		std::vector<T*>	m_data;
		OcTreeMgr<T>*	m_mgr;
		BoundingBox		m_bbox;
	};





	template <class T> class OcTreeMgr
	{
	public:
		friend class OcTree<T>;
		OcTreeMgr() : m_top(NULL),m_size(0){
			m_freeTree.reserve(OCTREE_POOL_SIZE);
			m_treePool = new OcTree<T>[OCTREE_POOL_SIZE];

		}
		~OcTreeMgr(){
			delete[] m_treePool;
		}

		OcTree<T>*	Allocate(){
			if(m_freeTree.size())
			{
				OcTree<T>* t = m_freeTree.back();
				m_freeTree.pop_back();
				return t;
			}else
			{
				return m_treePool+(m_size++);
			}
		}
		void Free(OcTree<T>* t){
			m_freeTree.emplace_back(t);
		}
		void InsertElement(T* n)
		{
			BoundingSphere& bsphere = n->GetBounds();
			std::stack<OcTree<T>*> stack;
			if(!m_top)
			{
				float size = NearestPowerOfTwo(length(bsphere.GetRadius()+bsphere.GetCenter()));
				OcTree<T>* t = Allocate();
				*t = OcTree<T>(this,BoundingBox(vec3(-size,-size,-size),vec3(size,size,size)));
				m_top = t;
			}
			if(!m_top->m_bbox.Within(bsphere))
			{
				//need to increase size

				a_uint8 found = 0;
				while(!found)
				{
					
					BoundingBox bbox;
					a_uint8 slot =  GetBboxForParent(m_top->m_bbox,bbox,normalize(bsphere.GetCenter()-m_top->m_bbox.GetCenter()));
					OcTree<T>* parent = Allocate();
					*parent = OcTree<T>(this,bbox);
					parent->m_children[slot] = m_top;
					m_top = parent;
					if(m_top->m_bbox.Within(bsphere))
					{
						break;
					}
				}
			}

			stack.emplace(m_top);
			while(stack.size())
			{
				OcTree<T>* current = stack.top();
				stack.pop();
				a_uint8 stop = 0;
				for(a_uint32 i =0; i < MAX_OCSPACE && !stop; i++)
				{
					if(current->m_children[i] && current->m_children[i]->m_bbox.Within(bsphere))
					{
						stop = 1;
						stack.emplace(current->m_children[i]);
					}else if(!current->m_children[i])
					{
						BoundingBox bbox;
						BboxFrom(current->m_bbox,bbox,i);
						if(bbox.Within(bsphere))
						{
							OcTree<T>* child = Allocate();
							*child = OcTree<T>(this,bbox);
							current->m_children[i] = child;
							stack.emplace(child);
							stop = 1;
						}
					}
				}
				if(!stop)
				{
					if(m_elements.find(n) !=m_elements.end() && m_elements[n] == current)
						break; // always in same octree_node;
					m_elements[n] = current;
					current->m_data.emplace_back(n);
				}
				
			}
			
		}
		OcTree<T>* Top() { return m_top; }
	private:
		std::map<T*,OcTree<T>*>   m_elements;
		OcTree<T>*				  m_top; // top of octree
		OcTree<T>*				  m_treePool;
		a_uint32			      m_size;
		std::vector<OcTree<T>*>   m_freeTree;

	};


	template <class T>  OcTree<T>::OcTree()
	{
	}
	template <class T>  OcTree<T>::OcTree(OcTreeMgr<T>* mgr,BoundingBox& bbox) : m_mgr(mgr),m_bbox(bbox)
	{
		std::memset(m_children,NULL,sizeof(m_children));
		m_data.reserve(100);
	}

	#include "Octree.inl"

}

#endif /*	OCTREE_H	*/

