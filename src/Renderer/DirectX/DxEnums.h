/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _DXENUMS_H_
#define _DXENUMS_H_

#include <Core/Enums.h>
#include <windows.h>
#include <string>
#include <CommonDefines.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

namespace Agmd
{
    class DXEnum
    {
    public :

//         struct TPixelFmt {GLenum Format, Internal, Type, _Format;};
//         
//         static unsigned long BufferFlags(unsigned long flags);
// 
//         static unsigned long DXEnum::LockBitsFlags(unsigned long flags);
// 
//         static unsigned long LockFlags(unsigned long flags);
// 
//         static GLenum Get(TMatrixType value);
// 
//         static std::string GetName(TMatrixType value);
// 
//         static TPixelFmt Get(TPixelFormat value);
// 
//         static GLenum Get(TBlend value);
// 
//         static GLenum Get(TDepth value);
// 
//         static GLenum Get(TTextureOp value);
// 
//         static GLenum Get(TTextureArg value);
// 
//         static GLenum Get(TRenderParameter value);
// 
//         static GLenum Get(TRenderMode value);
// 
//         static GLenum Get(TShaderType value);
// 
//         static GLenum GetAttachment(a_uint32 value);
// 
//         static GLenum Get(TComponent value);
// 
//         static GLenum Get(TTextureType value);

           static D3D_PRIMITIVE_TOPOLOGY        Get(TPrimitiveType value);


    private :

           static D3D_PRIMITIVE_TOPOLOGY        PrimitiveType[];
    };

}

#endif /* _DXENUMS_H_ */