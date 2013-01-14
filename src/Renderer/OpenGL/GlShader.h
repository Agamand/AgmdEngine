/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _GLSHADER_H_
#define _GLSHADER_H_

#include <AgmdDefines.h>
#include <Core/Shader/BaseShader.h>
#include <string>

namespace Agmd
{
    class GLShader : public BaseShader
    {
    public:
        GLShader(uint32 shaderid, TShaderType type);
        virtual ~GLShader();

        uint32 GetId() {return m_Shader;}

    private:
        uint32 m_Shader;
    };
}

#endif /* _GLSHADER_H_ */