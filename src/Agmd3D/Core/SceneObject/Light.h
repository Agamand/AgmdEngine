/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <Core/Buffer/Buffer.h>
#include <Core/Shader/ShaderProgram.h>
#include <Transform.h>
#include <Vector3.h>
#include <Matrix4.h>

using namespace AgmdMaths;

namespace Agmd
{
    enum LightType
    {
        LIGHT_DIR,
        LIGHT_POINT,
        LIGHT_SPOT
    };


    class AGMD3D_EXPORT Light
    {
    public:
        Light(vec3 pos, vec3 dir, LightType type);

        ~Light();

        void Prepare();
        void Bind();

        void BeginPrepareShadow() const;
        void EndPrepareShadow() const;

        void BeginApplyShadow() const;
        void EndApplyShadow() const;

        Transform& GetTransform();
        void SetPosition(vec3& position);
        const vec3& GetPosition();

    private:
        struct LightBuffer 
        {
            vec4    position;
            vec4    dir;
            vec4    ambient;
            vec4    diffuse;
            vec4    specular;
            float   innerAngle;
            float   outerAngle;
            float   range;
            int     type;
        };
        
        vec3        m_position;
        vec3        m_dir;
        vec3        m_ambient;
        vec3        m_diffuse;
        vec3        m_specular;
        float       m_innerAngle;
        float       m_outerAngle;
        float       m_range;
        LightType   m_Type;

        Transform m_Transform; //NOT IMPLEMENTED

        Buffer<LightBuffer> m_uniformLightBuffer;
    };
}

#endif /* _LIGHT_H_ */