#ifndef _SCENE_H_
#define _SCENE_H_


#include <Core/SceneNode/SceneNode.h>
#include <Core/SceneObject/Light.h>
#include <vector>
namespace Agmd
{
	class Scene
	{
	public:
		Scene();

		void Render(TRenderPass pass) const;

		void Draw() const;
	
		void Compute() const;

		void AddNode(SceneNode *node); // add to root

	    const std::vector<Light*>& GetLights();
		void AddLight(Light* l)
		{
			m_light.push_back(l);
		}
	private:
		std::vector<Light*> m_light; // static light
		std::vector<SceneNode*> m_displayable;
		SceneNode* m_root;
	};

}


#endif /* _SCENE_H_ */
