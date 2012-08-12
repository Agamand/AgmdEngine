#ifndef EFFECT_SHADOWMAP_H
#define EFFECT_SHADOWMAP_H

#include <Core\Effects\Effect.h>
#include <Core\Texture.h>

namespace Agmd
{

	class EffectShadowMap : public Effect
	{
	public:
		EffectShadowMap();

		virtual void Init() {};
		virtual void ApplyEffect();
		virtual void Update(uint64 t_diff) {};

	private:
		Texture shadowtex;
	}

}

#endif