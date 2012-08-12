#ifndef EFFECT_H
#define EFFECT_H

#include <Core\ShaderProgram.h>
#include <Core\FrameBuffer.h>

namespace Agmd
{

	class Effect
	{
	public:
		Effect() {}
		~Effect() {}

		virtual void Init() = 0;
		virtual void Update( uint64 /*t_diff*/) = 0;
		virtual void ApplyEffect() = 0;

	protected:
		ShaderProgram m_ShaderEffect;
		FrameBufferPtr m_FrameBuffer;

	}

}


#endif