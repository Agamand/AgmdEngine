#include <Core/Shader/ShaderPreCompiler.h>

#include <fstream>
#include <sstream>


SINGLETON_IMPL(Agmd::ShaderPreCompiler);

namespace Agmd
{

	const string ShaderPreCompiler::LoadAndCompileShader( const string& current_file, string const* current_dir )
	{
		string path;
		if(!current_dir)
			path = SolvePath(current_file); 
		else
			path  = *current_dir+"\\"+current_file;

		File f(path);

		if(shader_map.find(path) != shader_map.end())
			return shader_map[path];
	
		ifstream stream(path);
		std::stringstream buffer;
		char cbuffer = 0;
		std::string _path = f.Path();
		try
		{
		
			while (stream.read(&cbuffer,1) > 0)
			{
				std::string instruction = "";
				std::string value = "";

				switch(cbuffer)
				{
				case '#':
					while(stream.read(&cbuffer,1) > 0 && cbuffer != ' ')
						instruction += cbuffer;

					while(stream.read(&cbuffer,1) > 0 && cbuffer != '\n')
						value += cbuffer;

					value += '\n';
					switch(preprocessor(instruction))
					{
					case PREPROCESSOR_INCLUDE:
						if(value.find_first_of('"') != std::string::npos)
							buffer << LoadAndCompileShader(value.substr(value.find_first_of('"')+1, value.find_last_of('"')-1),&_path);
						else if(value.find_first_of('<') != std::string::npos)
							buffer << LoadAndCompileShader(value.substr(value.find_first_of('<')+1, value.find_last_of('>')-1),NULL);
						break;
					default:
						buffer << "#" << instruction << " " << value << "\n";
						break;
					}
					break;
				case '\n':
					buffer << cbuffer;
					break;
				case ' ':
				case '\t':
				case '\r':
					continue;
				default:
					buffer << cbuffer;
					while(stream.read(&cbuffer,1) > 0  && cbuffer != '\n')
						buffer <<cbuffer;

					buffer << '\n';
					break;
				}
			}
		}
		catch (std::exception e)
		{
			printf("ex %s",e.what());
		}
		return buffer.str();
	}

	ShaderPreCompiler::ShaderPreprocessor ShaderPreCompiler::preprocessor( const std::string& instruction )
	{
		if(!instruction.compare("include"))
		{
			return PREPROCESSOR_INCLUDE;
		}

		if(!instruction.compare("revision"))
		{
			return PREPROCESSOR_REVISION;
		}
		return PREPROCESSOR_UNKNOW;
	}

	std::string ShaderPreCompiler::SolvePath( string path )
	{
		for (std::set<string>::const_iterator itr = shader_path.begin(); itr != shader_path.end(); itr++ )
		{
			File f(*itr+"/"+path);
			if(f.Exists())
				return f.Fullname();
		}
		return path;
	}

	void ShaderPreCompiler::AddSearchPath( std::string param1 )
	{
		shader_path.insert(param1);
	}

	
}
