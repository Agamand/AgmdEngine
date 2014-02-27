#ifndef _SCENEMGR_H_
#define _SCENEMGR_H_

#include <Config/Export.h>
#include <Config/Fwd.h>
#include <Core/SceneNode/SceneNode.h>
#include <Core/SceneNode/DisplayNode.h>
#include <Core/SceneNode/LightNode.h>
#include <Core/SceneObject/Light.h>
#include <vector>
#include <queue>
namespace Agmd
{
	class AGMD3D_EXPORT SceneMgr
	{
	public:
		SceneMgr();

		void Render(TRenderPass pass) const;

		void Draw() const;
		void Compute();
		void Update();
		void FindVisible(std::vector<DisplayNode*>&,std::vector<LightNode*>&);

		void AddNode(SceneNode *node); // add to root

	    const std::vector<Light*>& GetLights();
		void AddLight(Light* l)
		{
			m_light.push_back(l);
		}
	private:
		std::vector<Light*> m_light; // static light
		std::vector<DisplayNode*> m_displayable;
		SceneNode* m_root;
	};

}


#endif /* _SCENEMRG_H_ */
