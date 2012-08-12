#include <Renderer\OpenGL\GlShaderProgram.h>
#include <Renderer\OpenGL\GlRenderer.h>

namespace Agmd
{
	GLShaderProgram::GLShaderProgram(uint32 id) :
	m_id(id)
	{
		SetupShader();
	}

	GLShaderProgram::~GLShaderProgram()
	{
		GLRenderer::glDeleteProgram(m_id);
	}

	void GLShaderProgram::SetupShader()
	{
		int32 n = 0;
		GLRenderer::glGetProgramiv( m_id, GL_ACTIVE_UNIFORMS, &n );

		for( int i = 0 ; i < n ; i++ )
		{
			Parameter var;
			char name[30] = "\0";
			size_t length = 0;
			GLRenderer::glGetActiveUniform( m_id, i, sizeof(name), (GLsizei*)&length, (GLint*)&var.size, &var.typeValue, name );
			var.loc = GLRenderer::glGetUniformLocation( m_id, name );
			var.type = PARAMETER_UNIFORM;
			m_UniformMap[name] = var;
		}

		GLRenderer::glGetProgramiv( m_id, GL_ACTIVE_ATTRIBUTES, &n );

		for( int i = 0 ; i < n ; i++ )
		{
			Parameter var;
			char name[30] = "\0";
			size_t length = 0;
			GLRenderer::glGetActiveAttrib( m_id, i, sizeof(name), (GLsizei*)&length, (GLint*)&var.size, &var.typeValue, name );
			var.loc = GLRenderer::glGetAttribLocation( m_id, name );
			var.type = PARAMETER_ATTRIBUT;
			m_AttributMap[name] = var;
		}
		Use(true);
		SetParameter("texture0",0);
		SetParameter("texture1",1);
		SetParameter("texture2",2);
		SetParameter("texture3",3);
		SetParameter("texture4",4);
		SetParameter("texture5",5);
		Use(false);
	}

	GLShaderProgram::Parameter GLShaderProgram::GetParameter(std::string name)
	{
		Parameter var;
		var.type = PARAMETER_NOFOUND;

		if(m_UniformMap.find(name) != m_UniformMap.end())
		{
			return m_UniformMap[name];
		}
		if(m_AttributMap.find(name) != m_AttributMap.end())
		{
			return m_AttributMap[name];
		}
		return var;
	}

	void GLShaderProgram::SetParameter(std::string name, float value)
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform1f(var.loc, value);
		else if(var.type == PARAMETER_ATTRIBUT)
			GLRenderer::glVertexAttrib1f(var.loc, value);


	}

	void GLShaderProgram::SetParameter(std::string name, vec2 value)
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform2f(var.loc, value.x, value.y);
		else if(var.type == PARAMETER_ATTRIBUT)
			GLRenderer::glVertexAttrib2f(var.loc, value.x, value.y);
	}

	void GLShaderProgram::SetParameter(std::string name, vec3 value)
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform3f(var.loc, value.x, value.y, value.z);
		else if(var.type == PARAMETER_ATTRIBUT)
			GLRenderer::glVertexAttrib3f(var.loc, value.x, value.y, value.z);
	}

	void GLShaderProgram::SetParameter(std::string name, vec4 value)
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform4f(var.loc, value.x, value.y, value.z, value.w);
		else if(var.type == PARAMETER_ATTRIBUT)
			GLRenderer::glVertexAttrib4f(var.loc, value.x, value.y, value.z, value.w);
	}

	void GLShaderProgram::SetParameter(std::string name, int value)
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform1i(var.loc, value);
	}

	void GLShaderProgram::SetParameter(std::string name, ivec2 value)
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform2i(var.loc, value.x, value.y);
	}

	void GLShaderProgram::SetParameter(std::string name, ivec3 value)
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform3i(var.loc, value.x, value.y, value.z);
	}

	void GLShaderProgram::SetParameter(std::string name, ivec4 value)
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform4i(var.loc, value.x, value.y, value.z, value.w);
	}

	void GLShaderProgram::SetParameter(std::string name, mat2 value)
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniformMatrix2fv(var.loc, 1, 0, value_ptr(value));
	}

	void GLShaderProgram::SetParameter(std::string name, mat3 value)
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniformMatrix3fv(var.loc, 1, 0, value_ptr(value));
	}

	void GLShaderProgram::SetParameter(std::string name, mat4 value)
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniformMatrix4fv(var.loc, 1, 0, value_ptr(value));
	}

	void GLShaderProgram::Use(bool use)
	{
 		GLRenderer::glUseProgram(use ? m_id : 0);
	}
}