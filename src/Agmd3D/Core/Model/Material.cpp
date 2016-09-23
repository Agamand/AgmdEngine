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
#include <Core/SceneNode/LightNode.h>
#include <Core/Model/SceneMgr.h>
#include <AgmdUtilities/Utilities/StringUtils.h>

using namespace AgmdUtilities;

namespace Agmd
{
    Material::Material(TRenderType type /*= TYPE_DIFFUSE*/) :
        m_shaderPipeline(ShaderPipeline::GetDefaultPipeline()),
        m_queueType(type)
    {
        Driver& render = Driver::Get();
        //         m_bufferMaterial = render.CreateUniformBuffer<MaterialInfo>(1,0,0);
        //         m_materialInfo.m_baseColor = Color::white;
        //         m_materialInfo.m_materialFlags = 0;
        //         MaterialInfo* info = (MaterialInfo*) m_bufferMaterial.Lock(0,1,0);
        //         *info = m_materialInfo;
        //         m_bufferMaterial.Unlock();
    }

    Material::Material(ShaderPipeline* pipeline, TRenderType type/*= TYPE_DIFFUSE*/) :
        m_shaderPipeline(pipeline),
        m_queueType(type)
    {
        Driver& render = Driver::Get();
        //         m_bufferMaterial = render.CreateUniformBuffer<MaterialInfo>(1,0,0);
        //         m_materialInfo.m_baseColor = Color::white;
        //         m_materialInfo.m_materialFlags = 0;
        //         MaterialInfo* info = (MaterialInfo*) m_bufferMaterial.Lock(0,1,0);
        //         *info = m_materialInfo;
        //         m_bufferMaterial.Unlock();
    }

    Material::Material(const Material& mat) : m_shaderPipeline(mat.m_shaderPipeline)
    {
        for (int i = 0; i < MAX_TEXTUREUNIT; i++)
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

        if (!m_shaderPipeline->Enable(pass))
            return false;


        //         SceneMgr* scene = render.GetActiveScene();
        //         Light::LightBuffer* buffer = scene->GetLightBuffer();
        // 
        //         float* _buffer = reinterpret_cast<float*>(buffer);
        //int size = sizeof(Light::LightBuffer)*10;

        /*
        struct lightInfoStruct
        {
        vec4 l_position;
        vec4 l_dir;
        vec4 l_ambient;
        vec4 l_diffuse;
        vec4 l_specular;
        float l_innerAngle;
        float l_outerAngle;
        float l_range;
        int l_type;
        };        
        */
        //         int lCount = scene->GetLightNodes().size();
        //         for(int i = 0; i <lCount && i < MAX_LIGHT; ++i)
        //         {
        //             (m_shaderPipeline)->m_pipeline[pass].SetParameter(StringBuilder("u_light[")(i)("].l_position"  ),buffer[i].position);
        //             (m_shaderPipeline)->m_pipeline[pass].SetParameter(StringBuilder("u_light[")(i)("].l_dir")       ,buffer[i].dir);
        //             (m_shaderPipeline)->m_pipeline[pass].SetParameter(StringBuilder("u_light[")(i)("].l_ambient")   ,buffer[i].ambient);
        //             (m_shaderPipeline)->m_pipeline[pass].SetParameter(StringBuilder("u_light[")(i)("].l_diffuse")   ,buffer[i].diffuse);
        //             (m_shaderPipeline)->m_pipeline[pass].SetParameter(StringBuilder("u_light[")(i)("].l_specular")  ,buffer[i].specular);
        //             (m_shaderPipeline)->m_pipeline[pass].SetParameter(StringBuilder("u_light[")(i)("].l_innerAngle"),buffer[i].innerAngle);
        //             (m_shaderPipeline)->m_pipeline[pass].SetParameter(StringBuilder("u_light[")(i)("].l_outerAngle"),buffer[i].outerAngle);
        //             (m_shaderPipeline)->m_pipeline[pass].SetParameter(StringBuilder("u_light[")(i)("].l_range")     ,buffer[i].range);
        //             (m_shaderPipeline)->m_pipeline[pass].SetParameter(StringBuilder("u_light[")(i)("].l_type")      ,buffer[i].type);
        //         }
        //         (m_shaderPipeline)->m_pipeline[pass].SetParameter("u_lightCount",lCount);
        for (a_uint32 i = 0; i < MAX_TEXTUREUNIT; i++)
        {
            if (m_texture[i].pass & (1 << pass))
            {
                render.SetTexture(i, m_texture[i].tex.GetTexture());
                textureFlags |= 1 << i;
            }
        }
        render.SetTextureFlag(textureFlags);
        return true;
    }

    void Material::Disable() const
    {
        m_shaderPipeline->Disable();
    }

    void Material::SetTexture(Texture tex, a_uint32 unit, TRenderPass pass)
    {
        m_texture[unit] = TextureUnit(tex, pass);
    }

    Texture Material::getTexture(int texUnit)
    {
        return m_texture[texUnit].tex;
    }

    TRenderType Material::GetRenderQueue()
    {
        return m_queueType;
    }

    void Material::SetRenderQueue(TRenderType type)
    {
        m_queueType = type;
    }
}
