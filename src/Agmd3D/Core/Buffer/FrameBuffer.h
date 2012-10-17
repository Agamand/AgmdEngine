#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <Core\Texture.h>
#include <Core/Buffer/RenderBuffer.h>
#include <Core\Enums.h>
#include <Utilities\SmartPtr.h>
#include <map>
//#include <vector>

namespace Agmd
{
	/*typedef std::vector<BindTexture> TextureVector;
	/struct BindTexture
	{
		BindTexture(TAttachment _attach, TextureBase* _tex) :
		attach(_attach),
		tex(_tex)
		{}

		TAttachment attach;
		TextureBase* tex;
	};*/

	typedef std::map<TAttachment,Texture> TextureMap;
	typedef std::map<TAttachment,RenderBuffer*> RenderBufferMap;

	class AGMD_EXPORT FrameBuffer
	{
	public:
		FrameBuffer();
		virtual ~FrameBuffer();

		virtual void setTexture(Texture, TAttachment) = 0;
		virtual void setTextureCube(Texture, TAttachment, int face) = 0;
		virtual void setRender(RenderBuffer*, TAttachment) = 0;
	
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual void Clear() = 0;

	protected:
		TextureMap		m_TextureMap;
		RenderBufferMap	m_RenderBufferMap;
	};

	typedef SmartPtr<FrameBuffer> FrameBufferPtr;

}

#endif //FRAMEBUFFER_H
