/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _TXTLOADER_H_
#define _TXTLOADER_H_

#include <Core/Loader.h>
#include <string>

namespace Agmd
{
    class TxtLoader : public Loader<char>
    {
    public :

        TxtLoader();

        ~TxtLoader();

        virtual char* LoadFromFile(const std::string& filename);

    private :

        static void OnError();
    };
}


#endif /* _TXTLOADER_H_*/
