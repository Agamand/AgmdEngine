#include <Renderer/OpenGL/GlUniformBuffer.h>
#include <Renderer/OpenGL/GlRenderer.h>

namespace Agmd
{
	GLUniformBuffer::GLUniformBuffer(unsigned long count, unsigned int buffer, unsigned int bindPoint) : 
	GLBuffer(count,buffer),
	m_bindPoint(bindPoint)
	{}

	unsigned int GLUniformBuffer::getBindPoint() const
	{
		return m_bindPoint;
	}
}