#ifndef TEXTUREBASE_H
#define TEXTUREBASE_H

#include <Config/Fwd.h>
#include <Vector2.h>
#include <Core/Enums.h>
#include <Core/Resource.h>
#include <Core/Image.h>


namespace Agmd
{

    class AGMD_EXPORT TextureBase : public Resource
    {
    public :

        virtual ~TextureBase();

		TTextureType GetType() const;

    protected :
        friend class Texture;

        TextureBase(const ivec2& size, TPixelFormat format, TTextureType type, bool hasMipmaps, bool autoMipmaps);


        virtual void Update(const AgmdMaths::Rectangle& rect) = 0;

		virtual void SetActiveTexture(int32 id) = 0;


        TPixelFormat m_Format;
        ivec2		 m_Size;
        Image        m_Data;
		TTextureType m_Type;
        bool         m_HasMipmaps;
        bool         m_AutoMipmaps;
		int32		 activeTexture; // -1 : Cube MAP / 0-5 : Texture X+ to Z-;
    };

}


#endif //TEXTUREBASE_H
