/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <Core/Loader.h>
#include <Core/Model/Model.h>
#include <Core/Enums.h>
#include <istream>


namespace Agmd
{
    class ObjLoader : public Loader<Model>
    {
    public :

        ObjLoader();
        ~ObjLoader();

        virtual Model* LoadFromFile(const std::string& filename);
        virtual void SaveToFile(const Model* object, const std::string& filename);
        
    private :
        
        bool skipCommentLine(std::istream& file);
        void skipLine(std::istream& file);
        bool processLine(a_vector<vec3>& position,a_vector<vec2>& texPos,a_vector<vec3>& normal,a_vector<Model::TIndex>& indices, std::istream& is);
        static void OnError();
    };

}


#endif //OBJLOADER_H