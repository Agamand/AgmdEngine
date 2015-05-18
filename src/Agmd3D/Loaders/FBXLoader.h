/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _FBXLOADER_H_
#define _FBXLOADER_H_

#include <Core/Loader.h>
#include <Core/Model/Model.h>
#include <Core/Enums.h>
#include <istream>


namespace Agmd
{
    class FBXLoader : public Loader<Model>
    {
    public :

        FBXLoader();
        ~FBXLoader();

        virtual Model* LoadFromFile(const std::string& filename);
        virtual void SaveToFile(const Model* object, const std::string& filename);

    private :

        static void OnError();
    };

}


#endif /* _FBXLOADER_H_ */