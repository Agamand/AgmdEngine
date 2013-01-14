/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <Config/Fwd.h>
#include <Config/Export.h>
#include <Core/Shader/ShaderProgram.h>
#include <Core/Texture/Texture.h>
#include <Core/Buffer/Buffer.h>
#include <Core/Enums.h>
#include <Core/Resource.h>
#include <Utilities/Color.h>

namespace Agmd
{
    struct AGMD3D_EXPORT TextureUnit
    {
        TextureUnit() :
        pass(0)
        {}

        TextureUnit(Texture _tex, uint32 _pass = 0) : 
        tex(_tex),
        pass(_pass)
        {}

        Texture tex;
        uint32 pass;

    };

    struct MaterialInfo
    {
        Color m_baseColor;
        uint32 m_materialFlags;
    };

    class AGMD3D_EXPORT Material : public Resource
    {
    public:
        Material();
        Material(ShaderPipeline* pipeline);
        ~Material();

        bool Enable(TRenderPass pass) const;
        void Disable() const;

        void SetTexture(Texture tex, uint32 unit, TRenderPass pass);

    private:
        ShaderPipeline* m_pipeline;
        TextureUnit m_texture[MAX_TEXTUREUNIT];
        MaterialInfo m_materialInfo;
        Buffer<MaterialInfo> m_bufferMaterial;
    }; 
}

#endif /* _MATERIAL_H_ */
