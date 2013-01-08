#ifndef GLFRAMEBUFFER_H
#define GLFRAMEBUFFER_H

#include <AgmdDefines.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Texture/TextureBase.h>

namespace Agmd
{

	class GLFrameBuffer : public FrameBuffer
	{
	public:
		GLFrameBuffer(uint32 buff_id);
		~GLFrameBuffer();

		virtual void setTexture(Texture tex, TAttachment attach);
		virtual void setTextureCube(Texture, TAttachment, int face);
		virtual void setRender(RenderBuffer* render, TAttachment attach);

		virtual void Bind();
		virtual void UnBind();

		virtual void Clear(uint32 flags);

		virtual void DrawBuffer(uint32 flag);
        virtual void DrawBuffers(uint32 nbuffer, uint32 flag[]);
		virtual void ReadBuffer(uint32 flag);

		uint32 GetID();

	private:
		uint32 m_Id;
	};

}

#endif //GLFRAMEBUFFER_H
