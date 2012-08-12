#include <Config/Fwd.h>
#include <Core/BaseShaderProgram.h>
#include <Utilities/SmartPtr.h>


namespace Agmd
{
    class AGMD_EXPORT ShaderProgram
    {
    public :

		void Create(BaseShader* vertex, BaseShader* eval, BaseShader* control, BaseShader* geom, BaseShader* frag);

		void LoadFromFile(const std::string& filename);

		void ReloadFromFile(const std::string& filename);

        void Unload();

        const BaseShaderProgram* GetShaderProgram() const;

		inline void Enable();

		inline void Disable();

		template <class T> inline void SetParameter(std::string name, T value);

    private :

        SmartPtr<BaseShaderProgram, ResourceCOM> m_ShaderProgram;
    };

	#include "ShaderProgram.inl"

}