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


namespace Agmd
{
    class AGMD3D_EXPORT DeferredRendering : public RenderingMode
    {
    public:
        DeferredRendering(int width, int height);
        DeferredRendering(ivec2 screen);
        ~DeferredRendering();

        virtual void Compute();

        virtual void Start();
        virtual void End();

        Texture GetDiffuseTexture();
        Texture GetNormalTexture();
        Texture GetPositionTexture();

    private:
        void Init();

        FrameBuffer* m_framebuffer;
        RenderBuffer* m_depthbuffer;
        RenderBuffer* m_colorbuffer;
        RenderBuffer* m_normalbuffer;
        RenderBuffer* m_positionbuffer;

        Texture m_textureBuffer[3];



    }; 
}


#endif /* _DEFERRED_RENDERING_H_ */
