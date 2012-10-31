#include <Config/Fwd.h>
#include <Core/Shader/BaseShaderProgram.h>
#include <Utilities/SmartPtr.h>

#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

using namespace AgmdUtilities;

namespace Agmd
{
    class AGMD_EXPORT ShaderProgram
    {
    public :

		void Create(BaseShader* vertex, BaseShader* eval, BaseShader* control, BaseShader* geom, BaseShader* frag);

		void LoadFromFile(const std::string& filename);

		void ReloadFromFile(const std::string& filename);

        void Unload();

        BaseShaderProgram* GetShaderProgram() const;

		inline void Enable();

		inline void Disable();

		template <class T> inline void SetParameter(TMatrixType type, T value);
		template <class T> inline void SetParameter(std::string name, T value);
		template <class T> inline void SetParameter(std::string name, T value, uint32 size);
		template <class T> inline void SetParameter(std::string name, Buffer<T> buf);

    private :

        SmartPtr<BaseShaderProgram, ResourceCOM> m_ShaderProgram;
    };

	#include "ShaderProgram.inl"

}

#endif //SHADERPROGRAM_H