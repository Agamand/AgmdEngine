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
#include <Core/Tools/BoundingBox.h>

using namespace AgmdMaths;

namespace Agmd
{
	class LightNode;
	class AGMD3D_EXPORT DisplayNode : public SceneNode
	{
	public :
		DisplayNode(Transform* t,Material*mat);
		virtual ~DisplayNode(){};

		virtual void Render(TRenderPass pass) const = 0;
		virtual void Draw() const = 0;

		virtual void FindVisible(Camera*cam, std::vector<DisplayNode*>& display,std::vector<LightNode*>& light);

		const Material& GetMaterial() const { return *m_material;}
		const BoundingBox& GetBoundingBox() const { return m_localBBox;};
		const BoundingBox& GetGlobalBoundingBox() const { return m_globalBbox;};

		virtual bool IsVisible( BoundingBox& bbox );

	protected:
		BoundingBox m_baseBbox;
		BoundingBox m_localBBox;
		BoundingBox m_globalBbox;
		Material* m_material;
	};

}


#endif /* _DISPLAYNODE_H_ */