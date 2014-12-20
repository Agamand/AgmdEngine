/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _DISPLAYNODE_H_
#define _DISPLAYNODE_H_

#include <Config/Fwd.h>
#include <Core/Resource.h>
#include <Core/Enums.h>
#include <Utilities/SmartPtr.h>
#include <Transform.h>
#include <Core/SceneNode/SceneNode.h>
#include <Core/Tools/RenderQueue.h>
#include <Core/Tools/BoundingBox.h>

using namespace AgmdMaths;

namespace Agmd
{
	class AGMD3D_EXPORT CameraNode : public SceneNode
	{
	public :
		CameraNode(Transform* t,Controller);
		virtual ~CameraNode(){};

		virtual void findVisible(Camera*cam, RenderQueue& display, a_vector<LightNode*>& light);

		virtual bool isVisible( BoundingBox& bbox );
		virtual bool update(Transform* transform, bool updateChildren, bool transformChanged);
	protected:

	};

}


#endif /* _DISPLAYNODE_H_ */