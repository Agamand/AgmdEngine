#ifndef TERRAIN_H
#define TERRAIN_H

#include <Vector2.h>
#include <Core/SceneObject/Model.h>

/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <string>

namespace Agmd
{
    
    class AGMD3D_EXPORT Terrain : public Model
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