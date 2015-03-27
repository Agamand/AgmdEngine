/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Model/Material.h>
#include <Core/Driver.h>
#include <Core/Shader/ShaderPipeline.h>


namespace Agmd
{
    Material::Material() : 
    m_pipeline(ShaderPipeline::GetDefaultPipeline())
    {
        Driver& render = Driver::Get();
        m_bufferMaterial = render.CreateUniformBuffer<MaterialInfo>(1,0,0);
        m_materialInfo.m_baseColor = Color::white;
        m_materialInfo.m_materialFlags = 0;
        MaterialInfo* info = (MaterialInfo*) m_bufferMaterial.Lock(0,1,0);
        *info = m_materialInfo;
        m_bufferMaterial.Unlock();
    }

    Material::Material(ShaderPipeline* pipeline) :
    m_pipeline(pipeline)
    {
        Driver& render = Driver::Get();
        m_bufferMaterial = render.CreateUniformBuffer<MaterialInfo>(1,0,0);
        m_materialInfo.m_baseColor = Color::white;
        m_materialInfo.m_materialFlags = 0;
        MaterialInfo* info = (MaterialInfo*) m_bufferMaterial.Lock(0,1,0);
        *info = m_materialInfo;
        m_bufferMaterial.Unlock();
    }

    Material::Material( const Material& mat ) : m_pipeline(mat.m_pipeline)
    {
        for(int i = 0 ; i < MAX_TEXTUREUNIT;i++)
            m_texture[i] = mat.m_texture[i];
    }

    Material::~Material()
    {
        m_bufferMaterial.Release();
    } 

    bool Material::Enable(TRenderPass pass) const
    {
        Driver& render = Driver::Get();
        a_uint32 textureFlags = 0;

        if(!m_pipeline->Enable(pass))
            return false;

        for(a_uint32 i = 0; i < MAX_TEXTUREUNIT; i++)
        {
            if(m_texture[i].pass & (1<<pass))
            {
                render.SetTexture(i,m_texture[i].tex.GetTexture());
                textureFlags |= 1<<i;
            }
        }
        render.SetTextureFlag(textureFlags);
        return true;
    }

    void Material::Disable() const
    {
        m_pipeline->Disable();
    }

    void Material::SetTexture(Texture tex, a_uint32 unit, TRenderPass pass)
    {
        m_texture[unit] = TextureUnit(tex,pass);
    }

    Texture Material::getTexture( int texUnit )
    {
        return m_texture[texUnit].tex;
    }

}