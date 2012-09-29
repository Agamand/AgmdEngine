#ifndef GLRENDERBUFFER_H
#define GLRENDERBUFFER_H

#include <Core/Buffer/RenderBuffer.h>
namespace Agmd
{

	class GLRenderBuffer : public RenderBuffer
	{
	public:
		GLRenderBuffer(uint32 buff_id, ivec2 size);
		~GLRenderBuffer();

		uint32 GetID();

	private:
		uint32 m_Id;
	};

}

#endif //GLRENDERBUFFER_H
