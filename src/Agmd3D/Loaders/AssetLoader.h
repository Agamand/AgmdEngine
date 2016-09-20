/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef ASSETJLOADER_H
#define ASSETJLOADER_H
#include <Config/Export.h>
#include <Core/Loader.h>
#include <Core/Model/Model.h>
#include <Core/Enums.h>
#include <istream>


namespace Agmd
{
	struct Mesh {
		std::string name;
		a_vector<Model::TVertex> vertices;
		a_vector<Model::TIndex> indices;
		Material* material;
		Mesh() : material(NULL) {}
	};


    class AGMD3D_EXPORT AssetLoader : public Loader<SceneNode>
    {
    public :

        AssetLoader();
        ~AssetLoader();

        virtual SceneNode* LoadFromFile(const std::string& filename);
		virtual Mesh* LoadSingleMesh(const std::string& filename, const std::string name);
        virtual void SaveToFile(const Model* object, const std::string& filename);
        
    private:
        static void OnError();
    };

}


#endif //ASSETJLOADER_H