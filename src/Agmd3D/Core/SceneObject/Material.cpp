#include <Core/SceneObject/Material.h>
#include <Core/Renderer.h>
#include <Core/Shader/ShaderPipeline.h>


namespace Agmd
{
    Material::Material() : 
    m_pipeline(ShaderPipeline::GetDefaultPipeline())
    {
        Renderer& render = Renderer::Get();
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
        Renderer& render = Renderer::Get();
        m_bufferMaterial = render.CreateUniformBuffer<MaterialInfo>(1,0,0);
        m_materialInfo.m_baseColor = Color::white;
        m_materialInfo.m_materialFlags = 0;
        MaterialInfo* info = (MaterialInfo*) m_bufferMaterial.Lock(0,1,0);
        *info = m_materialInfo;
        m_bufferMaterial.Unlock();
    }

    Material::~Material()
    {
        m_bufferMaterial.Release();
    } 

    bool Material::Enable(TRenderPass pass) const
    {
        Renderer& render = Renderer::Get();
        uint32 textureFlags = 0;

        if(!m_pipeline->Enable(pass))
            return false;

        for(uint32 i = 0; i < MAX_TEXTUREUNIT; i++)
        {
            if(m_texture[i].pass & pass)
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

    void Material::SetTexture(Texture tex, uint32 unit, TRenderPass pass)
    {
        m_texture[unit] = TextureUnit(tex,pass);
    }

}