/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _GLRENDERBUFFER_H_
#define _GLRENDERBUFFER_H_

#include <Core/Buffer/RenderBuffer.h>

namespace Agmd
{
    class GLRenderBuffer : public RenderBuffer
    {
    public:
        GLRenderBuffer(a_uint32 buff_id, const ivec2& size);
        ~GLRenderBuffer();

        a_uint32 GetID();

    private:
        a_uint32 m_Id;
    };
}

#endif /* _GLRENDERBUFFER_H_ */
