/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _POSTEFFECT_H_
#define _POSTEFFECT_H_

#include <Core/Shader/ShaderProgram.h>
#include <Core/Texture/Texture.h>

#include <AgmdDefines.h>

namespace Agmd
{

    class PostEffect
    {
    public:

        virtual void Init() = 0;
        virtual void Update( uint64 /*t_diff*/) = 0;
        virtual void ApplyEffect(Texture& input, Texture& output) = 0;

    protected:
        ShaderProgram m_program;

    };

}


#endif /* _POSTEFFECT_H_ */