/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _GLFRAMEBUFFER_H_
#define _GLFRAMEBUFFER_H_

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

        virtual void SetTexture(Texture tex, TAttachment attach);
        virtual void SetTextureCube(Texture, TAttachment, int face);
        virtual void SetRender(RenderBuffer* render, TAttachment attach);

        virtual void Bind();
        virtual void UnBind();

        virtual void Clear(uint32 flags);

        virtual void DrawBuffer(uint32 flag);
        virtual void DrawBuffers(uint32 nbuffer, uint32* flag);
        virtual uint32* GenerateBufferFlags(uint32 count, uint32 flags[]);
        virtual void ReadBuffer(uint32 flag);

        uint32 GetID();

    private:
        uint32 m_Id;
    };

}

#endif /* _GLFRAMEBUFFER_H_ */
