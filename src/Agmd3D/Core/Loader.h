/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef LOADER_H
#define LOADER_H

#include <Config/Fwd.h>
#include <Debug/Exception.h>
#include <string>


namespace Agmd
{
    template <class T>
    class Loader
    {
    public :

        virtual ~Loader()
        {
        }

        virtual T* LoadFromFile(const std::string& filename)
        {
            throw LoadingFailed(filename, "Le loader enregistré pour ce format ne prend pas en charge l'importation");
        }

        virtual void SaveToFile(const T* object, const std::string& filename)
        {
            throw LoadingFailed(filename, "Le loader enregistré pour ce format ne prend pas en charge l'exportation");
        }

    protected :

        Loader()
        {
        }
    };
}


#endif // LOADER_H
