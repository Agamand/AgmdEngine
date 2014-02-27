#ifndef _DEFERRED_RENDERING_H_
#define _DEFERRED_RENDERING_H_

#include <Config/Fwd.h>
#include <Config/Export.h>

/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Texture/Texture.h>
#include <Core/RenderingMode/RenderingMode.h>
#include <Core/Shader/ShaderProgram.h>
#include <Core/ShadowMapRenderer.h>


namespace Agmd
{
    enum TLightShader
    {
        DIRECTIONNAL,
        POINT,
        SPOT,
        DIRECTIONNAL_WITH_SHADOW,
        POINT_WITH_SHADOW,
        SPOT_WITH_SHADOW
    };
    #define MAX_LIGHT_SHADER 6

    class AGMD3D_EXPORT DeferredRendering : public RenderingMode
    {
    public:
        DeferredRendering(int width, int height);
        DeferredRendering(ivec2& screen);
        ~DeferredRendering();

        virtual void Compute();

        virtual void Start();
        virtual void End();

        Texture GetDiffuseTexture();
        Texture GetNormalTexture();
        Texture GetPositionTexture();
        inline Texture GetDepthTexture()
        {
            return m_textureBuffer[5];
        }

        ShadowMapRenderer* GetShadowRenderer();

    private:
        void Init();

        FrameBuffer* m_framebuffer;
        RenderBuffer* m_depthbuffer;
        RenderBuffer* m_colorbuffer;
        RenderBuffer* m_normalbuffer;
        RenderBuffer* m_positionbuffer;

        Texture m_textureBuffer[6];
        a_uint32* bufferFlags;
        
        ShaderProgram m_light_program[MAX_LIGHT_SHADER];

        ShadowMapRenderer* m_shadowRender;
        Texture m_depthCubemap;


    }; 
}


#endif /* _DEFERRED_RENDERING_H_ */
