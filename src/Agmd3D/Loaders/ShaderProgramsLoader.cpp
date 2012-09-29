#include <Loaders/ShaderProgramsLoader.h>
#include <Core/Renderer.h>
#include <Debug/New.h>
#include <iostream>
#include <string>
#include <fstream>

namespace Agmd
{

	ShaderProgramsLoader::ShaderProgramsLoader()
	{}

	ShaderProgramsLoader::~ShaderProgramsLoader()
	{}

	BaseShaderProgram* ShaderProgramsLoader::LoadFromFile(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::in);
		std::string stream = "", buffer;

		BaseShader* shader[5] = {NULL};
		int32 actualShader = -1;

		if (!file)
			throw LoadingFailed(filename,"Erreur lors du chargement du fichier (ShadersLoader)");

		while(std::getline(file,buffer))
		{
			if(!buffer.find("-- Vertex"))
			{
				if(actualShader >= 0 && !shader[actualShader])
				{
					shader[actualShader] = Renderer::Get().CreateShader(stream, (TShaderType)actualShader);
				}

				stream = "";
				actualShader = SHADER_VERTEX;
			}
			else if(!buffer.find("-- TessControl"))
			{
				if(actualShader >= 0 && !shader[actualShader])
				{
					shader[actualShader] = Renderer::Get().CreateShader(stream, (TShaderType)actualShader);
				}

				stream = "";
				actualShader = SHADER_TESS_CONTROL;
			}
			else if(!buffer.find("-- TessEval"))
			{
				if(actualShader >= 0 && !shader[actualShader])
				{
					shader[actualShader] = Renderer::Get().CreateShader(stream, (TShaderType)actualShader);
				}

				stream = "";
				actualShader = SHADER_TESS_EVALUATION;
			}
			else if(!buffer.find("-- Geometry"))
			{
				if(actualShader >= 0 && !shader[actualShader])
				{
					shader[actualShader] = Renderer::Get().CreateShader(stream, (TShaderType)actualShader);
				}

				stream = "";
				actualShader = SHADER_GEOMETRY;
			}
			else if(!buffer.find("-- Fragment"))
			{
				if(actualShader >= 0 && !shader[actualShader])
				{
					shader[actualShader] = Renderer::Get().CreateShader(stream, (TShaderType)actualShader);
				}

				stream = "";
				actualShader = SHADER_PIXEL;
			}else
			{
				stream += buffer;
				stream += "\n";
			}
		}
		
		if(actualShader >= 0 && !shader[actualShader])
		{
			shader[actualShader] = Renderer::Get().CreateShader(stream, (TShaderType)actualShader);
		}


		file.close();
		BaseShaderProgram* program = Renderer::Get().CreateShaderProgram(shader[0],shader[1],shader[2],shader[3],shader[4]);
		for(int32 i = 0; i < 5; i++)
			delete shader[i];
		return program;
	}

	void ShaderProgramsLoader::OnError()
	{
		throw Exception("");
	}


}
