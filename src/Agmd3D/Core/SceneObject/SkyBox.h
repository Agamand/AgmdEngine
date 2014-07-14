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

#include <container/Vector.h>

namespace Agmd
{



    class AGMD3D_EXPORT SkyBox
    {
    public:
        SkyBox();
        ~SkyBox();

        void Render() const;
        void Draw() const;
        void SetTexture(Texture tex);

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