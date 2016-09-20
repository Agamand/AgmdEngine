/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _BLURMOTIONEFFECT_H_
#define _BLURMOTIONEFFECT_H_

#include <Core/Effects/PostEffect.h>

namespace Agmd
{
    class AGMD3D_EXPORT BlurMotionEffect : public PostEffect
    {
    public:
        BlurMotionEffect(const ivec2& screen_size);
        //~BlurEffect();

        virtual void Init();
        virtual void Update(a_uint64 /*t_diff*/);
        virtual void ApplyEffect(Texture& input, Texture& output);

        void SetIntensity(float a);
    private:
        Texture m_accumulate;
    };
}
#endif /*_BLURMOTIONEFFECT_H_*/
