#ifndef TEXTUREBASE_H
#define TEXTUREBASE_H

#include <Config/Fwd.h>
#include <Maths/Vector2.h>
#include <Core/Enums.h>
#include <Core/Resource.h>
#include <Core/Image.h>


namespace Agmd
{

    class AGMD_EXPORT TextureBase : public Resource
    {
    public :

        virtual ~TextureBase();

    protected :
        friend class Texture;

        TextureBase(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps);

        virtual void Update(const Rectangle& rect) = 0;

        TPixelFormat m_Format;
        ivec2		 m_Size;
        Image        m_Data;
        bool         m_HasMipmaps;
        bool         m_AutoMipmaps;
    };

}


#endif //TEXTUREBASE_H
