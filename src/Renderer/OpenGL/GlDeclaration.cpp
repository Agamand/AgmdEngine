/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer/OpenGL/GLDeclaration.h>


namespace Agmd
{

    GLDeclaration::GLDeclaration(a_uint32 vaoID) : m_Elements(8), m_vertexArray(vaoID)
    {}

    GLDeclaration::~GLDeclaration()
    {}

    void GLDeclaration::AddElement(unsigned int stream, const GLDeclaration::TElement& element)
    {
        m_Elements[stream].push_back(element);
    }

    const GLDeclaration::TElementArray& GLDeclaration::GetStreamElements(unsigned int stream) const
    {
        return m_Elements[stream];
    }

    const a_uint32 GLDeclaration::GetVertexArray() const
    {
        return m_vertexArray;
    }
}
