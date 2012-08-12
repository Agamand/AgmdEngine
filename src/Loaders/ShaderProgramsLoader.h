#ifndef SHADERPROGRAMSLOADER_H
#define SHADERPROGRAMSLOADER_H

#include <Core/Loader.h>
#include <Core/ShaderProgram.h>
#include <Core/Enums.h>


namespace Agmd
{
    class ShaderProgramsLoader : public Loader<BaseShaderProgram>
    {
    public :

        ShaderProgramsLoader();

        ~ShaderProgramsLoader();

        virtual BaseShaderProgram* LoadFromFile(const std::string& filename);

    private :

        static void OnError();

    };

}


#endif //SHADERPROGRAMSLOADER_H
