#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <Core/Buffer/Buffer.h>
#include <Core/Shader/ShaderProgram.h>
#include <Vector3.h>
#include <Matrix4.h>

namespace Agmd
{
    enum LightType
    {
        LIGHT_DIR,
        LIGHT_POINT,
        LIGHT_SPOT
    };


    class Light
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

    private:
        struct LightBuffer 
        {
            vec4 position;
            vec4 dir;
            vec4 ambient;
            vec4 diffuse;
            vec4 specular;
            float innerAngle;
            float outerAngle;
            float range;
            int type;
        };

        vec3 m_position;
        vec3 m_dir;
        vec3 m_ambient;
        vec3 m_diffuse;
        vec3 m_specular;
        float m_innerAngle;
        float m_outerAngle;
        float m_range;
        LightType m_Type;
        
        Buffer<LightBuffer> m_uniformLightBuffer;
        ShaderProgram m_program;
        ShaderProgram m_program_shadowCast;
        ShaderProgram m_program_shadowUse;
    };
}

#endif /* _LIGHT_H_ */