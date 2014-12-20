/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef SCENEORLD_H
#define SCENEOLD_H

#include <Config/Export.h>
#include <Config/Fwd.h>
#include <Core/Texture/Texture.h>
#include <Core/Shader/ShaderProgram.h>
#include <Core/RenderObject/Displayable.h>
#include <Core/SceneObject/SkyBox.h>
#include <Core/SceneObject/Light.h>

#include <CommonDefines.h>

#include <vector>

namespace Agmd
{
    typedef a_vector<Displayable*> vDisplayable;

    class AGMD3D_EXPORT Scene
    {
    public:
        Scene();
        ~Scene();
        void Render(TRenderPass pass) const;

        void Draw() const;

        void Update(a_uint64 t_diff);

        void AddMesh(Displayable*);

        void AddLight(Light*);

        void SetSkyBox(SkyBox*);
        SkyBox* GetSkyBox();

        void RemoveMesh(Displayable*);

        const a_vector<Light*>& GetLights();

    private:

        vDisplayable        m_vMesh;
        SkyBox*             m_SkyBox;

        a_vector<Light*> m_lights;
    };


}


#endif //SCENEOLD_H