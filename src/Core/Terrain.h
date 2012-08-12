#ifndef TERRAIN_H
#define TERRAIN_H

#include <Maths\Vector2.h>
#include <Core\Model.h>

#include <string>

namespace Agmd
{
	
	class AGMD_EXPORT Terrain : public Model
	{
	public:
		Terrain(ivec2 _size, ivec2 _poly, std::string diffuse, std::string çheightmap);
		~Terrain();

		virtual void Render() const;

	private:

		void generate();

		Texture heightmap;
		ivec2 size;
		ivec2 n_poly;
	};

}

#endif