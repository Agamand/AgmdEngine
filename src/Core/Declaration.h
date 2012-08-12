#ifndef DECLARATION_H
#define DECLARATION_H

#include <Config/Export.h>
#include <Core/DeclarationElement.h>
#include <Utilities/SmartPtr.h>


namespace Agmd
{
    class AGMD_EXPORT Declaration
    {
    public :

        virtual ~Declaration() {}

    protected :

        Declaration() {}
    };

    typedef SmartPtr<Declaration> DeclarationPtr;

}


#endif // DECLARATION_H
