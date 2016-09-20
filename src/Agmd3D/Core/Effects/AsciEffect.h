/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _ASCIEFFECT_H_
#define _ASCIEFFECT_H_

#include <Core/Effects/PostEffect.h>

namespace Agmd
{
    class AGMD3D_EXPORT AsciEffect : public PostEffect
    {
    public:
        AsciEffect();
        //~AsciEffect();

        virtual void Init();
        virtual void Update(a_uint64 /*t_diff*/);
        virtual void ApplyEffect(Texture& input, Texture& output);

        void SetSpeed(float a);
    private:
        Texture m_asciTable;
        float m_speed;
        int m_time;
    };
}
#endif /*_ASCIEFFECT_H_*/
