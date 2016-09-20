/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _GLDECLARATION_H_
#define _GLDECLARATION_H_

#include <Core/Declaration.h>
#include <Container/Vector.h>

#include <CommonDefines.h>


namespace Agmd
{
    class GLDeclaration : public Declaration
    {
    public :

        struct TElement
        {
            a_uint32 usage;
            TElementType type;
            unsigned int offset;
        };

        typedef a_vector<TElement> TElementArray;
        typedef a_vector<TElementArray> TElementMatrix;

        GLDeclaration();

        ~GLDeclaration();

        void AddElement(unsigned int stream, const TElement& element);

        const TElementArray& GetStreamElements(unsigned int stream) const;

    private :

        TElementMatrix m_Elements;
    };
}


#endif /* _GLDECLARATION_H_ */
