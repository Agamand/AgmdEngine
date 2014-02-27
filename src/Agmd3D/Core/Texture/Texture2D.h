#ifndef _TEXTURE2D_H_
#define _TEXTURE2D_H_

#include <Core/Texture/Texture.h>
#include <Core/Texture/Image.h>

namespace Agmd
{
	class Texture2D : public Texture
	{
	public:
		Texture2D(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps);

		virtual TTextureType GetType() const;
	protected:
		Image        m_Data;
	};
}

#endif /* _TEXTURE2D_H_ */