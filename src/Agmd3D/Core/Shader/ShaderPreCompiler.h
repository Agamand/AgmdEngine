/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Config/Fwd.h>
#include <Utilities/SmartPtr.h>

#ifndef _SHADERPRECOMPILER_H_
#define _SHADERPRECOMPILER_H_

using namespace AgmdUtilities;
using namespace std;

#include <string>
#include <fstream>
#include <Config/Export.h>
#include <Utilities/Singleton.h>
#include <Utilities/File.h>
#include <set>
#include <map>

#define ESCAPE_SPACE_COND(c) (' ' == (c) || '\t' == (c) || '\r' == (c))

namespace Agmd
{
	

	class AGMD3D_EXPORT ShaderPreCompiler : public Singleton<ShaderPreCompiler>  
	{
		MAKE_SINGLETON(ShaderPreCompiler);
	public:
		enum ShaderPreprocessor
		{
			PREPROCESSOR_UNKNOW,
			PREPROCESSOR_INCLUDE,
			PREPROCESSOR_REVISION
		};

		const string LoadAndCompileShader(string& current_file, string const* current_dir);

		void AddSearchPath( std::string path);
	private:
		ShaderPreprocessor preprocessor(const std::string& instruction);
		inline bool escape_space(const char* c)
		{
			while(ESCAPE_SPACE_COND(*c) && *c != 0)
				c++;
			return true;
		}
		string SolvePath(string path);

		std::set<string> shader_path;
		std::map<string,string> shader_map;

	};
	
}

#endif /* _SHADERPRECOMPILER_H_ */
