#ifndef _SCENEMGR_H_
#define _SCENEMGR_H_

#include <Config/Export.h>
#include <Config/Fwd.h>
#include <Core/SceneNode/RootNode.h>
#include <Core/SceneNode/DisplayNode.h>
#include <Core/SceneNode/LightNode.h>
#include <Core/Model/Light.h>
#include <Core/Model/SkyBox.h>
#include <Container/Vector.h>
#include <Core/Tools/RenderQueue.h>
#if defined(USE_WX) && defined(USE_EDITOR)
class wxFrame;
#endif

#define MAX_LIGHT 10

namespace Agmd
{
    class AGMD3D_EXPORT SceneMgr
    {
    public:
        SceneMgr();

        void Render(TRenderPass pass, TRenderType type = TRenderType::TYPE_DIFFUSE) const;

        void Draw(TRenderType type = TRenderType::TYPE_DIFFUSE) const;
        void Compute();
        void Update();
        void FindVisible(RenderQueue&,a_vector<LightNode*>&);

        void AddNode(SceneNode* node); // add to root

        const a_vector<Light*>& GetLights();
        const a_vector<LightNode*>& GetLightNodes();
        void AddLight(Light* l);

        void SetSkybox(SkyBox* skybox);

        SkyBox* GetSkyBox();

        bool isEmpty() const
        {
            return !m_root || m_root->isEmpty();
        }

        void clear();

        const RenderQueue& getRenderQueue() { return m_renderQueue; }

        SceneNode* GetRoot()
        {
            return m_root;
        }

        Light::LightBuffer* GetLightBuffer();
    private:
        //event
        friend class RootNode;
        void __addNode(SceneNode*);
        void __removeNode(SceneNode*);

        a_vector<Light*> m_light; // static light
        a_vector<LightNode*> m_lights;
        RenderQueue m_renderQueue;
        RootNode* m_root;
        SkyBox* m_skybox;
        Light::LightBuffer m_lightBuffer[MAX_LIGHT];
#if defined(USE_WX) && defined(USE_EDITOR)
        wxFrame* m_frame;
#endif
    };
}


#endif /* _SCENEMRG_H_ */
