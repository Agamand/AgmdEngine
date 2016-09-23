/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef DECLARATION_H
#define DECLARATION_H

#include <Config/Export.h>
#include <Core/DeclarationElement.h>
#include <Utilities/SmartPtr.h>

using namespace AgmdUtilities;

namespace Agmd
{
    class AGMD3D_EXPORT Declaration
    {
    public :

        virtual ~Declaration()
        {
        }

    protected :

        Declaration()
        {
        }
    };

    typedef SmartPtr<Declaration> DeclarationPtr;
}


#endif // DECLARATION_H
