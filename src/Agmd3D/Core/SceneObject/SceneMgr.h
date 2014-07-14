#ifndef _SCENEMGR_H_
#define _SCENEMGR_H_

#include <Config/Export.h>
#include <Config/Fwd.h>
#include <Core/SceneNode/SceneNode.h>
#include <Core/SceneNode/DisplayNode.h>
#include <Core/SceneNode/LightNode.h>
#include <Core/SceneObject/Light.h>
#include <Core/SceneObject/SkyBox.h>
#include <Container/Vector.h>
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
		void FindVisible(a_vector<DisplayNode*>&,a_vector<LightNode*>&);

		void AddNode(SceneNode *node); // add to root

	    const a_vector<Light*>& GetLights();
		void AddLight(Light* l);

		void SetSkybox(SkyBox* skybox);

		SkyBox* GetSkyBox();
		bool isEmpty() const
		{
			return !m_root || m_root->isEmpty();
		}
		void clear();
	private:
		a_vector<Light*> m_light; // static light
		a_vector<DisplayNode*> m_displayable;
		SceneNode* m_root;
		SkyBox* m_skybox;
	};

}


#endif /* _SCENEMRG_H_ */
