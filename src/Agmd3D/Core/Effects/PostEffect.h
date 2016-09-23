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
#include <Core/Buffer/FrameBuffer.h>
#include <Utilities/SmartPtr.h>
#include <CommonDefines.h>

namespace Agmd
{
    class AGMD3D_EXPORT PostEffect
    {
    public:
        PostEffect();
        virtual ~PostEffect();
        virtual void Init() = 0;
        virtual void Update(a_uint64 /*t_diff*/) = 0;
        virtual void ApplyEffect(Texture& input, Texture& output) = 0;
        virtual void SetEnable(bool enable);
    protected:
        ShaderProgram m_program;
        FrameBuffer* m_framebuffer;
    };

    typedef AgmdUtilities::SmartPtr<PostEffect> PostEffectPtr;
}


#endif /* _POSTEFFECT_H_ */
