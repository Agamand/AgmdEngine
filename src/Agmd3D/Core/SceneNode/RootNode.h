/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _ROOTNODE_H_
#define _ROOTNODE_H_

#include <Config/Fwd.h>
#include <Config/Export.h>
#include <Core/SceneNode/SceneNode.h>

using namespace AgmdMaths;

namespace Agmd
{
	class SceneMgr;
	class AGMD3D_EXPORT RootNode : public SceneNode
	{
	public :
		RootNode(SceneMgr* mgr): SceneNode(ROOT_NODE),m_sceneMgr(mgr)
		{
			add(this);
		}

		void remove(SceneNode*);
		void add(SceneNode*);
// 		void update(SceneNode*){
// 
// 		}

	private:
		SceneMgr* m_sceneMgr;
	};

}

#endif /* _ROOTNODE_H_ */