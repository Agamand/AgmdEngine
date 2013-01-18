/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <Core/Texture/Texture.h>
#include <Core/Buffer/RenderBuffer.h>
#include <Core/Enums.h>
#include <Utilities/SmartPtr.h>

#include <vector>

namespace Agmd
{

    typedef std::vector<const Texture> TextureMap;
    typedef std::vector<RenderBuffer*> RenderBufferMap;

    class AGMD3D_EXPORT FrameBuffer
    {
    public:
        FrameBuffer();
        virtual ~FrameBuffer();

        virtual void SetTexture(const Texture&, uint32) = 0;
        virtual void SetTextureCube(const Texture&, uint32, int face) = 0;
        virtual void SetRender(RenderBuffer*, uint32) = 0;
    
        virtual void Bind() = 0;
        virtual void UnBind() = 0;
        virtual void Clear(uint32 flag = CLEAR_ALL) = 0;

        virtual void DrawBuffer(uint32 flag) = 0;
        virtual void DrawBuffers(uint32 nbuffer, uint32 flag[]) = 0;
        virtual uint32* GenerateBufferFlags(uint32 count, uint32 flags[]) = 0;
        virtual void ReadBuffer(uint32 flag) = 0;

    protected:
        TextureMap          m_TextureMap;
        RenderBufferMap     m_RenderBufferMap;
    };

    typedef SmartPtr<FrameBuffer> FrameBufferPtr;

}

#endif //FRAMEBUFFER_H
