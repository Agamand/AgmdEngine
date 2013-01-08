#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <Core/Loader.h>
#include <Core/SceneObject/Model.h>
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
        bool processLine(std::vector<vec3>& position,std::vector<vec2>& texPos,std::vector<vec3>& normal,std::vector<Model::TIndex>& indices, std::istream& is);
        static void OnError();
    };

}


#endif //OBJLOADER_H