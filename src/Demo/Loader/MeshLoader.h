/*
============================================================================
Demo - A test application !

Author : 
Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
Jean-Vincent Lamberti (https://github.com/Kinroux)

https://github.com/Agamand/AgmdEngine
status : in pause
============================================================================
*/

#ifndef MESHLOADER_H
#define MESHLOADER_H

#include <Core/Loader.h>
#include <Core/SceneObject/Model.h>
#include <Core/Enums.h>
#include <istream>

using namespace Agmd;

class MeshLoader : public Loader<Model>
{
public :

    MeshLoader();
    ~MeshLoader();

    virtual Model* LoadFromFile(const std::string& filename);
    virtual void SaveToFile(const Model* object, const std::string& filename);
        
private :
    static void OnError();
};



#endif /* MESHLOADER_H */