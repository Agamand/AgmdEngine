/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef ASSETJLOADER_H
#define ASSETJLOADER_H

#include <Core/Loader.h>
#include <Core/SceneObject/Model.h>
#include <Core/Enums.h>
#include <istream>


namespace Agmd
{
    class AssetLoader : public Loader<SceneNode>
    {
    public :

        AssetLoader();
        ~AssetLoader();

        virtual SceneNode* LoadFromFile(const std::string& filename);
        virtual void SaveToFile(const Model* object, const std::string& filename);
        
    private:
        static void OnError();
    };

}


#endif //ASSETJLOADER_H