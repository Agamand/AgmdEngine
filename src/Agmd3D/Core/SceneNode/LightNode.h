#ifndef _LIGHTNODE_H_
#define _LIGHTNODE_H_

#include <Core/SceneNode/SceneNode.h>
#include <Core/SceneObject/Light.h>

namespace Agmd{
	class LightNode : public SceneNode
	{
	public:
		LightNode(Transform* t,Light model);
		virtual bool IsVisible(BoundingBox&);
		const Light* GetLightModel() const;

	private:
		Light* m_model;
	};
}
#endif /* _LIGHTNODE_H_ */