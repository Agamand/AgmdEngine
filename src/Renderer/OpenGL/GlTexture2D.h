/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _GLTEXTURE2D_H_
#define _GLTEXTURE2D_H_

#include <Renderer/OpenGL/GlTexture.h>
#include <Core/Texture/Image.h>

namespace Agmd
{
    class GLTexture2D : public GLTexture
    {
    public :

        GLTexture2D(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps, a_uint32 texture);

        ~GLTexture2D();

        virtual TTextureType GetType() const;

        virtual Image* getPixels();
    private :

        virtual void Update(const AgmdMaths::Rectangle& rect);

        virtual void updatePixelFromTexture();

        Image m_Data;
    };
}


#endif /* _GLTEXTURE2D_H_ */
