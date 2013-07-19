#ifndef _SHADOWMAPRENDERER_H_
#define _SHADOWMAPRENDERER_H_

#include <Core/Buffer/FrameBuffer.h>
#include <Core/Texture/Texture.h>
#include <Core/SceneObject/Light.h>
#include <Core/Shader/ShaderProgram.h>
#include <Vector2.h>

namespace Agmd
{
    class AGMD3D_EXPORT ShadowMapRenderer
    {
    public:
        ShadowMapRenderer(const ivec2& size);
        ~ShadowMapRenderer();

        void Reset();
        void BeginLight(Light* l);
        void SetDepth(int face);
        void EndLight();
        void SetupForRendering();
        void SetOffset(float offset);
        Texture& GetShadowDepth();
        static mat4 bias;
    private:

        Texture m_depth[6];
        FrameBuffer* m_framebuffer;
        mat4 m_shadow_matrix[6];
        uint32 m_currentDepth;
        ivec2 m_shadowSize;
        LightType m_currentLightType;
        Light* m_currentLight;
        ShaderProgram m_shadowcast;
        static mat4 s_lookupMatrix[6];
        float m_offset;
    };
}

#endif
