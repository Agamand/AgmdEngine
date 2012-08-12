#ifndef GLDECLARATION_H
#define GLDECLARATION_H

#include <Core/Declaration.h>
#include <vector>


namespace Agmd
{
    class GLDeclaration : public Declaration
    {
    public :

        struct TElement
        {
            TElementUsage usage;
            TElementType  type;
            unsigned int  offset;
        };
        typedef std::vector<TElement>      TElementArray;
        typedef std::vector<TElementArray> TElementMatrix;

        GLDeclaration();

        ~GLDeclaration();

        void AddElement(unsigned int stream, const TElement& element);

        const TElementArray& GetStreamElements(unsigned int stream) const;

    private :

        TElementMatrix m_Elements;
    };

}


#endif // GLDECLARATION_H
