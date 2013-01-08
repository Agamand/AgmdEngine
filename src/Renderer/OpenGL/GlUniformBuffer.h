#ifndef _GLUNIFORMBUFFER_H_
#define _GLUNIFORMBUFFER_H_

#include <Renderer/OpenGL/GlBuffer.h>
#include <Renderer/OpenGL/GlEnums.h>

namespace Agmd
{
    class GLUniformBuffer : public GLBuffer<GL_UNIFORM_BUFFER>
    {
    public :
        GLUniformBuffer(unsigned long count, unsigned int buffer, unsigned int bindPoint);
        //virtual ~GLUniformeBuffer();

        virtual void Bind(uint32 bindpoint);

		unsigned int getBindPoint() const;

    private:
        unsigned int m_bindPoint;
    };

}


#endif /* _GLUNIFORMBUFFER_H_ */
