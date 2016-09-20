/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _SSAO_H_
#define _SSAO_H_

#include <Core/Effects/PostEffect.h>

namespace Agmd
{
    class AGMD3D_EXPORT Ssao : public PostEffect
    {
    public:
        Ssao(Texture& depth, Texture& normal, Texture& position, Texture& noise);

        virtual void Init();
        virtual void Update(a_uint64 /*t_diff*/);
        virtual void ApplyEffect(Texture& input, Texture& output);
    private:

        void CreateSsao(Texture& output);
        void ApplySsao(Texture& input, Texture& output);
        void ApplyBlur(Texture& input, Texture& output);
        ShaderProgram m_blurProgram;
        Texture m_depth;
        Texture m_normal;
        Texture m_position;
        Texture m_noise;
        Texture m_buffer[2];
    };
}
#endif /* _SSAO_H_ */
