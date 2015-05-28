/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/


#include <Core/Model/Light.h>
#include <Core/Buffer/Buffer.h>
#include <Core/Driver.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace Agmd
{
    Light::Light(vec3 pos, vec3 dir, LightType type)
    {
        m_lightBuffer.position = vec4(pos,1.0f);
        m_lightBuffer.dir = vec4(dir,1.0f);
        m_lightBuffer.ambient = vec4(vec3(1),1.0f);
        m_lightBuffer.diffuse = vec4(vec3(1),1.0f);
        m_lightBuffer.specular = vec4(vec3(1),1.0f);
        m_lightBuffer.innerAngle = cosf(50.0f/180.0f*(float)M_PI);
        m_lightBuffer.outerAngle = cosf(60.0f/180.0f*(float)M_PI);
        m_lightBuffer.range = 30.0f;
        m_lightBuffer.type = type;
        m_uniformLightBuffer = Driver::Get().CreateUniformBuffer<LightBuffer>(1, BUF_DYNAMIC, UNIFORM_LIGHT_BIND, 0, &m_lightBuffer);
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
        
        Driver::Get().SetCurrentProgram(nullptr);
    }

    Light::~Light()
    {}

    void Light::SetPosition(vec3& position)
    {
        if(position == vec3(m_lightBuffer.position))
            return;

        m_lightBuffer.position = vec4(position,1);
        vec3* new_pos =  m_uniformLightBuffer.LockBits<vec3>(0,sizeof(vec3),LOCK_WRITEONLY);
        *new_pos = position;
        m_uniformLightBuffer.Unlock();
    }

    void Light::SetDirection(vec3& direction)
    {
        if(m_lightBuffer.dir == vec4(direction,1))
            return;

        m_lightBuffer.dir = vec4(direction,1);
        vec3* new_dir =  m_uniformLightBuffer.LockBits<vec3>(sizeof(vec4),sizeof(vec3), LOCK_WRITEONLY);
        *new_dir = direction;
        m_uniformLightBuffer.Unlock();
    }

    void Light::SetRange(float range)
    {
        if(m_lightBuffer.range == range)
            return;

        m_lightBuffer.range = range;
        float* _range = m_uniformLightBuffer.LockBits<float>(22*sizeof(float),sizeof(float),LOCK_WRITEONLY);
        *_range = range;
        m_uniformLightBuffer.Unlock();
    }
    
    const vec3& Light::GetPosition()
    {
        return vec3(m_lightBuffer.position);
    }

    const vec3& Light::GetDirection()
    {
        return vec3(m_lightBuffer.dir);
    }

    LightType Light::GetType() const
    {
        return (LightType)m_lightBuffer.type;
    }

    float Light::GetRange() const
    {
        return m_lightBuffer.range;
    }

    float Light::GetOuterAngle() const
    {
        return m_lightBuffer.outerAngle;
    }

    float Light::GetInnerAngle() const
    {
        return m_lightBuffer.innerAngle;
    }

    void Light::FillBuffer( LightBuffer*data )
    {
        *data = m_lightBuffer;
    }

    void Light::SetOuter( float angle )
    {
        if(angle > 180.0f)
            angle = 180.0f;
        else if(angle < 0)
            angle = 0;
        m_lightBuffer.outerAngle = cosf(angle/180.0f*(float)M_PI);
        if(m_lightBuffer.outerAngle < m_lightBuffer.innerAngle)
            m_lightBuffer.outerAngle = m_lightBuffer.innerAngle;
        float* _outer = m_uniformLightBuffer.LockBits<float>((21)*sizeof(float),sizeof(float),LOCK_WRITEONLY);
        *_outer = m_lightBuffer.outerAngle;
        m_uniformLightBuffer.Unlock();
    }

    void Light::SetInner( float angle )
    {
        if(angle > 180.0f)
            angle = 180.0f;
        else if(angle < 0)
            angle = 0;
        

        m_lightBuffer.innerAngle = cosf(angle/180.0f*(float)M_PI);
        if(m_lightBuffer.innerAngle > m_lightBuffer.outerAngle)
            m_lightBuffer.innerAngle = m_lightBuffer.outerAngle;
        float* _inner = m_uniformLightBuffer.LockBits<float>((20)*sizeof(float),sizeof(float),LOCK_WRITEONLY);
        *_inner = m_lightBuffer.innerAngle;
        m_uniformLightBuffer.Unlock();
    }

    void Light::SetAngles( float inner,float outer )
    {
        if(inner > 180.0f)
            inner = 180.0f;
        else if(inner < 0)
            inner = 0;
        if(outer > 180.0f)
            outer = 180.0f;
        else if(outer < 0)
            outer = 0;

        if(inner > outer)
            inner = outer;


        m_lightBuffer.innerAngle = cosf(inner/180.0f*(float)M_PI);
        m_lightBuffer.outerAngle = cosf(outer/180.0f*(float)M_PI);
        float* angles = m_uniformLightBuffer.LockBits<float>((20)*sizeof(float),sizeof(float)*2,LOCK_WRITEONLY);
        *angles = m_lightBuffer.innerAngle;
        *(angles+1) = m_lightBuffer.outerAngle;
        m_uniformLightBuffer.Unlock();
    }

}