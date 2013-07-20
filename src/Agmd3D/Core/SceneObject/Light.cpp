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
#define _USE_MATH_DEFINES
#include <math.h>

namespace Agmd
{
    Light::Light(vec3 pos, vec3 dir, LightType type) :
    m_position(pos), m_dir(dir), m_Type(type), m_ambient(vec3(1)),
    m_diffuse(vec3(1.0)), m_specular(vec3(1)), m_range(30.0f),m_innerAngle(cos(50.0f/180.0f*M_PI)),
    m_outerAngle(cos(60.0f/180.0f*M_PI))
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
        m_uniformLightBuffer = Renderer::Get().CreateUniformBuffer<LightBuffer>(1, BUF_DYNAMIC, UNIFORM_LIGHT_BIND, 0, &lightBuffer);
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
        vec3* new_pos =  m_uniformLightBuffer.LockBits<vec3>(0,sizeof(vec3),LOCK_WRITEONLY);
        *new_pos = m_position;
        m_uniformLightBuffer.Unlock();
    }

    void Light::SetDirection(vec3& direction)
    {
        if(m_dir == direction)
            return;

        m_dir = direction;
        vec3* new_dir =  m_uniformLightBuffer.LockBits<vec3>(sizeof(vec4),sizeof(vec3), LOCK_WRITEONLY | LOCK_READONLY);
        *new_dir = m_dir;
        m_uniformLightBuffer.Unlock();
    }

    void Light::SetRange(float range)
    {
        if(m_range == range)
            return;

        m_range = range;
        float* _range = m_uniformLightBuffer.LockBits<float>(22*sizeof(float),sizeof(float),LOCK_WRITEONLY);
        *_range = m_range;
        m_uniformLightBuffer.Unlock();
    }
    
    const vec3& Light::GetPosition()
    {
        return m_position;
    }

    const vec3& Light::GetDirection()
    {
        return m_dir;
    }

    Transform& Light::GetTransform()
    {
        return m_Transform;
    }

    LightType Light::GetType() const
    {
        return m_Type;
    }

    float Light::GetRange() const
    {
        return m_range;
    }

    float Light::GetOuterAngle() const
    {
        return m_outerAngle;
    }

    float Light::GetInnerAngle() const
    {
        return m_innerAngle;
    }
}