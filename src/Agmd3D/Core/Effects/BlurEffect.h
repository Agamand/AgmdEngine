/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _BLUREFFECT_H_
#define _BLUREFFECT_H_

#include <Core/Effects/PostEffect.h>
namespace Agmd
{
    class AGMD3D_EXPORT BlurEffect : public PostEffect
    {
    public:
        BlurEffect(const Texture& depth);
        //~BlurEffect();

        virtual void Init();
        virtual void Update( uint64 /*t_diff*/);
        virtual void ApplyEffect(Texture& input, Texture& output);

        void SetNoiseOffset(float a);
    private:
        Texture m_depth;

    };
}
#endif /*_BLUREFFECT_H_*/
