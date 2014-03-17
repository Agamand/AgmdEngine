/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _GLFRAMEBUFFER_H_
#define _GLFRAMEBUFFER_H_

#include <CommonDefines.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Texture/TextureBase.h>

namespace Agmd
{

    class GLFrameBuffer : public FrameBuffer
    {
    public:
        GLFrameBuffer(a_uint32 buff_id);
        ~GLFrameBuffer();

        virtual void SetTexture(const Texture& tex, a_uint32 attach);
        virtual void SetTextureCube(const Texture& tes, a_uint32 attach, a_int32 face);
        virtual void SetRender(RenderBuffer* render, a_uint32 attach);

        virtual void Bind();
        virtual void UnBind();

        virtual void Clear(a_uint32 flags);

        virtual void DrawBuffer(a_uint32 flag);
        virtual void DrawBuffers(a_uint32 nbuffer, a_uint32* flag);
        virtual a_uint32* GenerateBufferFlags(a_uint32 count, a_uint32 flags[]);
		virtual a_uint32* GenerateBufferFlags(a_uint32* buffer,a_uint32 count, a_uint32 flags[]);
        virtual void ReadBuffer(a_uint32 flag);

        a_uint32 GetID();

    private:
        a_uint32 m_Id;
    };

}

#endif /* _GLFRAMEBUFFER_H_ */
