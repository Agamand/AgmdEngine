/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer/DirectX/DXDeclaration.h>


namespace Agmd
{

    DXDeclaration::DXDeclaration() : m_Elements(8)
    {}

    DXDeclaration::~DXDeclaration()
    {}

    void DXDeclaration::AddElement(unsigned int stream, const DXDeclaration::TElement& element)
    {
        m_Elements[stream].push_back(element);
    }

    const DXDeclaration::TElementArray& DXDeclaration::GetStreamElements(unsigned int stream) const
    {
        return m_Elements[stream];
    }

}
