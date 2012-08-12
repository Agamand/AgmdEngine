#ifndef SHADER_H
#define SHADER_H

//==========================================================
// En-têtes
//==========================================================
#include <Config/Fwd.h>
#include <Core/BaseShader.h>
#include <Maths/Vector2.h>
#include <Maths/Vector3.h>
#include <Maths/Vector4.h>
#include <Utilities/SmartPtr.h>
#include <string>


namespace Agmd
{
    class AGMD_EXPORT Shader
    {
    public :

        void LoadFromFile(const std::string& filename);

		void CreateFromSrc(const std::string& src, TShaderType type);

        void Unload();

        const BaseShader* GetShader() const;

    private :

        SmartPtr<BaseShader, ResourceCOM> m_Shader;
    };

}


#endif //SHADER_H