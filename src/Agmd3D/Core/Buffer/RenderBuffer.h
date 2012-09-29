#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include <Config\Export.h>
#include <Vector2.h>
#include <Utilities\SmartPtr.h>
#include <AgmdDefines.h>

using namespace AgmdUtilities;

namespace Agmd
{

	class AGMD_EXPORT RenderBuffer
	{
	public:
		RenderBuffer(ivec2 size);
		virtual ~RenderBuffer();
	protected:
		ivec2 m_Size;
	};

	typedef SmartPtr<RenderBuffer> RenderBufferPtr;

}

#endif //RENDERBUFFER_H
