#ifndef SKYBOX_H
#define SKYBOX_H

#include <Config\Fwd.h>
#include <Config\Export.h>

#include <Core\Sky.h>
#include <Core\Texture.h>
#include <Core\Declaration.h>
#include <Core\Buffer\Buffer.h>


#include <AgmdDefines.h>

#include <vector>

namespace Agmd
{



	class AGMD_EXPORT SkyBox : public Sky
	{
	public:
		SkyBox(float size = 1.0f);
		virtual ~SkyBox();

		virtual void Render() const;

		void SetTexture(Texture tex, uint32 index);
	private:

		struct TVertex
		{
			vec3 position;
			vec2 texcoord0;
		};
		typedef short TIndex;
		

		void Generate();

		Texture				m_Texture[6];
		DeclarationPtr		m_Declaration;
		Buffer<TVertex>		m_VertexBuffer;
        Buffer<TIndex>		m_IndexBuffer;
		BaseShaderProgram*	m_Program;
	

	};

}


#endif