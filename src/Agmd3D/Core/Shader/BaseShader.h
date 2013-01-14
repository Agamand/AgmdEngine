/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef BASESHADER_H
#define BASESHADER_H

#include <Core/Enums.h>
#include <Core/Resource.h>
#include <Matrix4.h>
#include <map>


namespace Agmd
{

    class AGMD3D_EXPORT BaseShader : public Resource
    {
    public :

        virtual ~BaseShader();

        TShaderType GetType() const;

    protected :
        friend class Shader;

        BaseShader(TShaderType Type);
        TShaderType m_Type;
    };
}


#endif //BASESHADER