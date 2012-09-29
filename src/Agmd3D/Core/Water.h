#ifndef WATER_H
#define WATER_H

#include <Vector2.h>
#include <Core/Model.h>


#include <string>

namespace Agmd
{

	struct WaveParameters
	{
		float speed;
		float amplitude;
		float wavelength;
		float steepness;
	};

	struct WaveDirections
	{
		float x;
		float z;
	};

	class AGMD_EXPORT Water : public Model
	{
	public:
		Water(ivec2 _size, ivec2 _poly);
		~Water();

		virtual void Render() const;
		void SetScene(Scene* sc);

	private:

		void generate();
		void GenerateRefraction() const;
		void GenerateReflection() const;
		ivec2 size;
		ivec2 n_poly;

		Scene* scene; // Scene use to make Reflection & Refraction texture
		BaseShaderProgram* m_program;
		TextureBase* m_ReflectionMap;
		TextureBase* m_RefractionMap;
		TextureBase* m_WaterTexture;
		FrameBuffer* fbo[2];
		RenderBuffer* m_MirrorTex;
	};

}

#endif //WATER_H