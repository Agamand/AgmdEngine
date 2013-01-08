
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
		m_uniformLightBuffer = Renderer::Get().CreateUniformBuffer<LightBuffer>(1, 0, UNIFORM_LIGHT_BIND, &lightBuffer);
	}

	void Light::Bind()
	{
        m_uniformLightBuffer.Bind(UNIFORM_LIGHT_BIND);
	}

	void Light::BeginPrepareShadow() const
	{
		if(m_Type != LIGHT_DIR)
			return;

		Renderer& render = Renderer::Get();
		render.SetCurrentProgram(m_program.GetShaderProgram());
		render.getPipeline()->SetParameter("light_dir",m_dir);
		render.getPipeline()->SetParameter("light_pos",m_position);
	}

	void Light::EndPrepareShadow() const
	{
		Renderer::Get().SetCurrentProgram(nullptr);
	}

	void Light::BeginApplyShadow() const
	{
		if(m_Type != LIGHT_DIR)
			return;
	}

	void Light::EndApplyShadow() const
	{
		
		Renderer::Get().SetCurrentProgram(nullptr);
	}

	Light::~Light()
	{}

}