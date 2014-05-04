/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Shader/ShaderPipeline.h>
#include <Core/Driver.h>



namespace Agmd
{
    ShaderPipeline::ShaderPipeline()
    {
    }

    ShaderPipeline::~ShaderPipeline()
    {
    }

    bool ShaderPipeline::Enable(TRenderPass pass) const
    {
        if(!m_pipeline[pass].GetShaderProgram())
            return false;
        Driver::Get().SetCurrentProgram(m_pipeline[pass].GetShaderProgram());
        return true;
    }

    void ShaderPipeline::Disable() const
    {
        Driver::Get().SetCurrentProgram(NULL);
    }

    ShaderPipeline* ShaderPipeline::s_defaultPipeline = NULL;

    ShaderPipeline* ShaderPipeline::GetDefaultPipeline()
    {
        if(!s_defaultPipeline)
        {
            LoadDefaultFunction();
            s_defaultPipeline = new ShaderPipeline();
            ShaderProgram defaultShader;
            defaultShader.LoadFromFile("Shader/RenderingShader/ZPassShader.glsl");
            s_defaultPipeline->m_pipeline[RENDERPASS_ZBUFFER] = defaultShader;
            defaultShader.LoadFromFile("Shader/RenderingShader/DiffuseShader.glsl");
            s_defaultPipeline->m_pipeline[RENDERPASS_DIFFUSE] = defaultShader;
            //defaultShader.LoadFromFile("Shader/RenderingShader/LightingShader.glsl");
            //s_defaultPipeline->m_pipeline[RENDERPASS_LIGHTING] = defaultShader;
            defaultShader.LoadFromFile("Shader/RenderingShader/DirectionnalShadowCastShader.glsl");
            s_defaultPipeline->m_pipeline[RENDERPASS_DIRECTIONNAL_LIGHTING_WITH_SHADOW] = defaultShader;
            defaultShader.LoadFromFile("Shader/RenderingShader/PointShadowCastShader.glsl");
            s_defaultPipeline->m_pipeline[RENDERPASS_POINT_SHADOW_CAST] = defaultShader;
            defaultShader.LoadFromFile("Shader/RenderingShader/DeferredShader.glsl");
            s_defaultPipeline->m_pipeline[RENDERPASS_DEFERRED] = defaultShader;
        }

        return s_defaultPipeline;
    }

    void ShaderPipeline::LoadDefaultFunction()
    {
        
    }

}