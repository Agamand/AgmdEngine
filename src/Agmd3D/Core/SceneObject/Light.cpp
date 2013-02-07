/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/


#include <Core/SceneObject/Light.h>
#include <Core/Buffer/Buffer.h>
#include <Core/Renderer.h>

namespace Agmd
{
    Light::Light(vec3 pos, vec3 dir, LightType type) :
    m_position(pos), m_dir(dir), m_Type(type), m_ambient(vec3(1)),
    m_diffuse(vec3(1.0)), m_specular(vec3(1)), m_range(30.0f),m_innerAngle(30.0f),
    m_outerAngle(40.0f)
    {
        LightBuffer lightBuffer;
        lightBuffer.position = vec4(m_position,1.0f);
        lightBuffer.dir = vec4(m_dir,1.0f);
        lightBuffer.ambient = vec4(m_ambient,1.0f);
        lightBuffer.diffuse = vec4(m_diffuse,1.0f);
        lightBuffer.specular = vec4(m_specular,1.0f);
        lightBuffer.innerAngle = m_innerAngle;
        lightBuffer.outerAngle = m_outerAngle;
        lightBuffer.range = m_range;
        lightBuffer.type = m_Type;
        m_uniformLightBuffer = Renderer::Get().CreateUniformBuffer<LightBuffer>(1, BUF_STREAM, UNIFORM_LIGHT_BIND, &lightBuffer);
    }

    void Light::Bind()
    {
        m_uniformLightBuffer.Bind(UNIFORM_LIGHT_BIND);
    }

    void Light::BeginPrepareShadow() const
    {}

    void Light::EndPrepareShadow() const
    {}

    void Light::BeginApplyShadow() const
    {}

    void Light::EndApplyShadow() const
    {
        
        Renderer::Get().SetCurrentProgram(nullptr);
    }

    Light::~Light()
    {}

    void Light::SetPosition(vec3& position)
    {
        if(position == m_position)
            return;

        m_position = position;
        vec4 new_pos = vec4(m_position,1.0f);
        LightBuffer* lightBuffer =  m_uniformLightBuffer.Lock(0);
        lightBuffer->position = vec4(m_position,1.0f);
        m_uniformLightBuffer.Unlock();
    }
    
    const vec3& Light::GetPosition()
    {
        return m_position;
    }

    Transform& Light::GetTransform()
    {
        return m_Transform;
    }

}