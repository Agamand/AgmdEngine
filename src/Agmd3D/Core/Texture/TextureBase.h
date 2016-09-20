/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef TEXTUREBASE_H
#define TEXTUREBASE_H

#include <Config/Fwd.h>
#include <Vector2.h>
#include <Core/Enums.h>
#include <Core/Resource.h>
#include <AgmdMaths/Rectangle.h>

namespace Agmd
{
    class AGMD3D_EXPORT TextureBase : public Resource
    {
    public :

        virtual ~TextureBase();

        virtual TTextureType GetType() const = 0;

        virtual Image* getPixels() = 0;

    protected :
        friend class Texture;

        TextureBase(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps);

        virtual void Update(const AgmdMaths::Rectangle& rect) = 0;
        virtual void updatePixelFromTexture() = 0;

        TPixelFormat m_Format;
        ivec2 m_Size;
        bool m_HasMipmaps;
        bool m_AutoMipmaps;
    };
}


#endif //TEXTUREBASE_H
