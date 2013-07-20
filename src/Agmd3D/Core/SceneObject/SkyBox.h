/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef SKYBOX_H
#define SKYBOX_H

#include <Config/Fwd.h>
#include <Config/Export.h>

#include <Core/Texture/Texture.h>
#include <Core/Declaration.h>
#include <Core/Buffer/Buffer.h>


#include <CommonDefines.h>

#include <vector>

namespace Agmd
{



    class AGMD3D_EXPORT SkyBox
    {
    public:
        SkyBox(float size = 1.0f);
        ~SkyBox();

        void Render() const;
        void Draw() const;
        void SetTexture(Texture tex, uint32 index);

    private:

        struct TVertex
        {
            vec3 position;
            //vec2 texcoord0;
        };
        typedef short TIndex;
        

        void Generate();

        Texture                 m_Texture;
        DeclarationPtr          m_Declaration;
        Buffer<TVertex>         m_VertexBuffer;
        Buffer<TIndex>          m_IndexBuffer;
        BaseShaderProgram*      m_Program;
    

    };

}


#endif