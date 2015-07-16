
#include <Transform.h>
#include <Core/Model/Model.h>
#include <Core/Model/Material.h>

#ifndef _ANODE_H_
#define _ANODE_H
using namespace AgmdMaths;





namespace Agmd{


	enum DirtyFlag
	{
		DTRANSFORM_UPDATE = 0x01,
		DBOUNDS_UPDATE = 0x02
	};



	class Camera;
	class AGMD3D_EXPORT ANode
	{
	public:
		friend class ASceneMgr;
		ANode(Model* m,Material* mat,Transform* t):
			m_model(m),
			m_material(mat),
			m_transform(t),
			m_controller(NULL),
			m_camera(NULL),
			m_parent(NULL),
			m_children(NULL),
			m_childrenCount(0),
			m_dirtyFlag(0)
		{
			if(m_model)
				m_baseBounds = m_localBounds = m_globalBounds = m_model->getBounding();
		}
		Model* GetModel() const { return m_model; }
		Transform& GetTransform() const { return *m_transform; }
		Material* GetMaterial() const { return m_material; }
		void SetController( Controller* controller );

		BoundingSphere& GetBounds(){ return m_globalBounds;}

		//private: // need to be private
		
		//what can be a node
		Model*            m_model;
		Transform*        m_transform;
		Material*		  m_material;
		Controller*       m_controller;
		Camera*			  m_camera;
		
		// for traversal tree
		ANode*			  m_parent; 
		ANode*			  m_children;
		a_uint32		  m_childrenCount;

		// for culling test
		BoundingSphere    m_baseBounds;
		BoundingSphere    m_localBounds;
		BoundingSphere    m_globalBounds;

		a_uint8 m_dirtyFlag;

	};
}
#endif /*_ANODE_H_*/