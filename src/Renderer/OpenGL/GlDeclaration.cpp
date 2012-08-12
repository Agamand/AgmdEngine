#include <Renderer/OpenGL/GLDeclaration.h>


namespace Agmd
{

	GLDeclaration::GLDeclaration() : m_Elements(8)
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

}
