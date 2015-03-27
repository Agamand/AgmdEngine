/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _DRUGEFFECT_H_
#define _DRUGEFFECT_H_

#include <Core/Effects/PostEffect.h>
namespace Agmd
{
    class AGMD3D_EXPORT DrugEffect : public PostEffect
    {
    public:
        DrugEffect();

        virtual void Init();
        virtual void Update( a_uint64 /*t_diff*/);
        virtual void ApplyEffect(Texture& input, Texture& output);
    private:
        float m_time;
    };
}
#endif /* _DRUGEFFECT_H_ */
