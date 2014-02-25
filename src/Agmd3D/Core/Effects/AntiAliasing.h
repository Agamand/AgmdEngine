/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _ANTIALIASING_H_
#define _ANTIALIASING_H_

#include <Core/Effects/PostEffect.h>
namespace Agmd
{
    class AGMD3D_EXPORT AntiAliasing : public PostEffect
    {
    public:
        AntiAliasing();

        virtual void Init();
        virtual void Update( a_uint64 /*t_diff*/);
        virtual void ApplyEffect(Texture& input, Texture& output);
        
        //void SetNoiseOffset(float a);
        void SetItrCount(int itr){iteration = itr >= 1 ? itr : 1;}
    private:

        void ApplyFxaa(Texture& input, Texture& output);

        Texture m_depth;
        int iteration;

    };
}
#endif /* _ANTIALIASING_H_ */
