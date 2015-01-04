/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _FORWARDRENDERING_H_
#define _FORWARDRENDERING_H_

#include <Config/Fwd.h>
#include <Config/Export.h>

#include <Core/Texture/Texture.h>
#include <Core/RenderingMode/RenderingMode.h>

namespace Agmd
{
    class AGMD3D_EXPORT ForwardRendering : public RenderingMode
    {
    public:
        ForwardRendering(int width, int height);
        ForwardRendering(ivec2& screen);
        ~ForwardRendering();

        virtual void compute();

        virtual void start();
        virtual void end();

        Texture getDiffuseTexture();
        Texture getLightingTexture();
        Texture getDepthTexture();
		void init();
    private:
        
        FrameBuffer* m_framebuffer;
        RenderBuffer* m_depthbuffer;
        Texture m_textureBuffer[3];
        a_uint32* bufferFlags[2];

    };
}

#endif /* _FORWARDRENDERING_H_ */
