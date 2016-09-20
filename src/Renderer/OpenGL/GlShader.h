/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _GLSHADER_H_
#define _GLSHADER_H_

#include <CommonDefines.h>
#include <Core/Shader/BaseShader.h>
#include <string>

namespace Agmd
{
    class GLShader : public BaseShader
    {
    public:
        GLShader(a_uint32 shaderid, TShaderType type);
        virtual ~GLShader();

        a_uint32 GetId() {return m_Shader;}

    private:
        a_uint32 m_Shader;
    };
}

#endif /* _GLSHADER_H_ */