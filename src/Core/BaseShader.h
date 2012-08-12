#ifndef BASESHADER_H
#define BASESHADER_H

#include <Core/Enums.h>
#include <Core/Resource.h>
#include <Maths/Matrix4.h>
#include <map>


namespace Agmd
{

    class AGMD_EXPORT BaseShader : public Resource
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