/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef IMAGESLOADER_H
#define IMAGESLOADER_H

#include <Core/Loader.h>


namespace Agmd
{
    class ImagesLoader : public Loader<Image>
    {
    public :

        ImagesLoader();

        ~ImagesLoader();

        virtual Image* LoadFromFile(const std::string& filename);

        virtual void SaveToFile(const Image* object, const std::string& filename);
    };
}


#endif //IMAGESLOADER_H
