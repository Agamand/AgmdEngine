/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _DXDECLARATION_H_
#define _DXDECLARATION_H_

#include <Core/Declaration.h>
#include <Container/Vector.h>

#include <CommonDefines.h>

#include <dxgi.h>
#include <d3d11.h>

namespace Agmd
{
    class DXDeclaration : public Declaration
    {
    public :

        DXDeclaration(ID3D11InputLayout* declaration);

        ~DXDeclaration();
        ID3D11InputLayout* GetDeclaration() const;
    private :

        ID3D11InputLayout* m_declaration;
    };

}


#endif /* _DXDECLARATION_H_ */
