#ifndef _TEXTURECUBE_H_
#define _TEXTURECUBE_H_

#include <Core/Texture/TextureBase.h>
#include <Core/Texture/Image.h>
#define MAX_FACE 6

namespace Agmd
{
	/*
	class TextureCube : public TextureBase
	{
	public:
		TextureCube(const ivec2& size, TPixelFormat format, bool hasMipmaps, bool autoMipmaps);

		virtual TTextureType GetType() const;
	protected:
		Image        m_Data[MAX_FACE];
	};*/
}

#endif /* _TEXTURECUBE_H_ */