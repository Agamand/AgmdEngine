#ifndef GLFRAMEBUFFER_H
#define GLFRAMEBUFFER_H

#include <AgmdDefines.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core\TextureBase.h>

namespace Agmd
{

	class GLFrameBuffer : public FrameBuffer
	{
	public:
		GLFrameBuffer(uint32 buff_id);
		~GLFrameBuffer();

		virtual void setTexture(TextureBase* tex, TAttachment attach);
		virtual void setRender(RenderBuffer* render, TAttachment attach);

		virtual void Bind();
		virtual void UnBind();

		virtual void Clear();

		uint32 GetID();

	private:
		uint32 m_Id;
	};

}

#endif //GLFRAMEBUFFER_H
