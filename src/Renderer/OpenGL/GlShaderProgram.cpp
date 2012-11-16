#include <Renderer\OpenGL\GlShaderProgram.h>
#include <Renderer\OpenGL\GlBuffer.h>
#include <Renderer\OpenGL\GlUniformBuffer.h>
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

		/*GLRenderer::glGetProgramiv( m_id, GL_ACTIVE_UNIFORM_BLOCKS, &n );

		for( int i = 0 ; i < n ; i++ )
		{
			Parameter var;
			char name[30] = "\0";
			int32 length = 0;
			GLRenderer::glGetActiveUniformBlock( m_id, i,GL_UNIFORM_BLOCK_NAME_LENGTH,&length);
			var.loc = GLRenderer::glGetAttribLocation( m_id, name );
			var.type = PARAMETER_UNIFORM_BLOCK;
			m_AttributMap[name] = var;
		}*/

		Use(true);
		SetParameter("texture0",0);
		SetParameter("texture1",1);
		SetParameter("texture2",2);
		SetParameter("texture3",3);
		SetParameter("texture4",4);
		SetParameter("texture5",5);
		SetParameter("u_shadowMap",10);
		Use(false);

		for(int i = 0; i < MAX_APIMATRIX; i++)
		{
			Parameter par = GetParameter(RGLEnum::GetName((TMatrixType)(MAT_MODEL+i)));
			m_APIMatrix[i] = par;
		}
	}

	GLShaderProgram::Parameter GLShaderProgram::GetParameter(std::string name) const
	{
		Parameter var;
		var.type = PARAMETER_NOFOUND;
		ParameterMap::const_iterator itr;
		if((itr = m_UniformMap.find(name)) != m_UniformMap.end())
		{
			return itr->second;
		}
		if((itr = m_AttributMap.find(name)) != m_AttributMap.end())
		{
			return itr->second;
		}
		return var;
	}

	void GLShaderProgram::SetParameter(std::string name, float value) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform1f(var.loc, value);
		else if(var.type == PARAMETER_ATTRIBUT)
			GLRenderer::glVertexAttrib1f(var.loc, value);


	}

	void GLShaderProgram::SetParameter(std::string name, vec2 value) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform2f(var.loc, value.x, value.y);
		else if(var.type == PARAMETER_ATTRIBUT)
			GLRenderer::glVertexAttrib2f(var.loc, value.x, value.y);
	}

	void GLShaderProgram::SetParameter(std::string name, vec3 value) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform3f(var.loc, value.x, value.y, value.z);
		else if(var.type == PARAMETER_ATTRIBUT)
			GLRenderer::glVertexAttrib3f(var.loc, value.x, value.y, value.z);
	}

	void GLShaderProgram::SetParameter(std::string name, vec4 value) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform4f(var.loc, value.x, value.y, value.z, value.w);
		else if(var.type == PARAMETER_ATTRIBUT)
			GLRenderer::glVertexAttrib4f(var.loc, value.x, value.y, value.z, value.w);
	}

	void GLShaderProgram::SetParameter(std::string name, int value) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform1i(var.loc, value);
	}

	void GLShaderProgram::SetParameter(std::string name, ivec2 value) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform2i(var.loc, value.x, value.y);
	}

	void GLShaderProgram::SetParameter(std::string name, ivec3 value) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform3i(var.loc, value.x, value.y, value.z);
	}

	void GLShaderProgram::SetParameter(std::string name, ivec4 value) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniform4i(var.loc, value.x, value.y, value.z, value.w);
	}

	void GLShaderProgram::SetParameter(std::string name, mat2 value) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniformMatrix2fv(var.loc, 1, 0, value_ptr(value));
	}

	void GLShaderProgram::SetParameter(std::string name, mat3 value) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniformMatrix3fv(var.loc, 1, 0, value_ptr(value));
	}

	void GLShaderProgram::SetParameter(std::string name, mat4 value) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniformMatrix4fv(var.loc, 1, 0, value_ptr(value));
	}

	void GLShaderProgram::SetParameter(std::string name, float* value, uint32 count) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
		{
			if(var.size < count)
				return;

			for(uint32 i = 0; i < 1; i++)
				GLRenderer::glUniform1fv(var.loc, count, (GLfloat*)value);
		}
	}

	void GLShaderProgram::SetParameter(std::string name, vec2* value, uint32 count) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
		{
			if(var.size < count)
				return;

			for(uint32 i = 0; i < 1; i++)
				GLRenderer::glUniform2fv(var.loc, count, (GLfloat*)value);
		}
	}

	void GLShaderProgram::SetParameter(std::string name, vec3* value, uint32 count) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
		{
			if(var.size < count)
				return;

			for(uint32 i = 0; i < 1; i++)
				GLRenderer::glUniform3fv(var.loc, count, (GLfloat*)value);
		}
	}

	void GLShaderProgram::SetParameter(std::string name, vec4* value, uint32 count) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
		{
			if(var.size < count)
				return;

			for(uint32 i = 0; i < 1; i++)
				GLRenderer::glUniform4fv(var.loc, count, (GLfloat*)value);
		}
	}

	void GLShaderProgram::SetParameter(std::string name, mat4* value, uint32 count) const
	{
		Parameter var = GetParameter(name);
		if(var.type == PARAMETER_UNIFORM)
		{
			if(var.size < count)
				return;

			for(uint32 i = 0; i < 1; i++)
				GLRenderer::glUniformMatrix4fv(var.loc, count, 0, (GLfloat*)value);
		}
	}

	void GLShaderProgram::SetParameter(TMatrixType type,mat4 value) const
	{
		Parameter var = m_APIMatrix[type];
		if(var.type == PARAMETER_UNIFORM)
			GLRenderer::glUniformMatrix4fv(var.loc, 1, 0, value_ptr(value));
	}

	void GLShaderProgram::SetParameter(std::string name, const BaseBuffer* buf) const
	{
		int32 index = GLRenderer::glGetUniformBlockIndex(m_id,name.c_str());
		if(index)
			GLRenderer::glUniformBlockBinding(m_id,static_cast<const GLUniformBuffer*>(buf)->getBindPoint(), index);
	}

	void GLShaderProgram::Use(bool use) const
	{
 		GLRenderer::glUseProgram(use ? m_id : 0);
	}
}