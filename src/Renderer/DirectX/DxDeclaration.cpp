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
    DXDeclaration::DXDeclaration(ID3D11InputLayout* declaration) : m_declaration(declaration)
    {
    }

    DXDeclaration::~DXDeclaration()
    {
    }

    ID3D11InputLayout* DXDeclaration::GetDeclaration() const
    {
        return m_declaration;
    }
}
