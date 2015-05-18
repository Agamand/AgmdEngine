/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer/DirectX/DxEnums.h>

namespace Agmd
{
//     GLenum DXEnum::MatrixType[] =
//     {
//         GL_MODELVIEW,
//         GL_PROJECTION,
//         GL_TEXTURE,
//         GL_TEXTURE,
//         GL_TEXTURE,
//         GL_TEXTURE
//     };
// 
//     std::string  DXEnum::MatrixName[] =
//     {
//         "u_matModel",
//         "u_matView",
//         "u_matProjection",
//         "texture0Matrix",
//         "texture1Matrix",
//         "texture2Matrix",
//         "texture3Matrix",
//         "normalMatrix",
//         "positionMatrix",
//         "rotationMatrix"
//     };
// 
//     DXEnum::TPixelFmt DXEnum::PixelFormat[] =
//     {
//         {GL_LUMINANCE,       GL_LUMINANCE8,                    GL_UNSIGNED_BYTE,              GL_RGBA},
//         {GL_LUMINANCE_ALPHA, GL_LUMINANCE8_ALPHA8,             GL_UNSIGNED_BYTE,              GL_RGBA},
//         {GL_BGRA,            GL_RGB5_A1,                       GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_RGBA},
//         {GL_BGRA,            GL_RGBA4,                         GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_RGBA},
//         {GL_BGR,             GL_RGB8,                          GL_UNSIGNED_BYTE,              GL_RGBA},
//         {GL_BGRA,            GL_RGBA8,                         GL_UNSIGNED_BYTE,              GL_RGBA},
//         {GL_BGR,             GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, 0,                             GL_RGBA},
//         {GL_BGRA,            GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, 0,                             GL_RGBA},
//         {GL_BGRA,            GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 0,                             GL_RGBA},
//         {GL_BGRA,            GL_DEPTH_COMPONENT32,             GL_UNSIGNED_BYTE,              GL_DEPTH_COMPONENT},
//         {GL_BGR,             GL_RGB16F,                        GL_UNSIGNED_BYTE,              GL_RGBA},
//         {GL_BGR,             GL_RGB32F,                        GL_UNSIGNED_BYTE,              GL_RGBA}
//     };
// 
//     GLenum DXEnum::Blend[] =
//     {
//         GL_SRC_ALPHA,
//         GL_ONE_MINUS_SRC_ALPHA,
//         GL_DST_ALPHA,
//         GL_ONE_MINUS_DST_ALPHA,
//         GL_SRC_COLOR,
//         GL_ONE_MINUS_SRC_COLOR,
//         GL_DST_COLOR,
//         GL_ONE_MINUS_DST_COLOR,
//         GL_ONE,
//         GL_ZERO
//     };
// 
//     GLenum DXEnum::Depth[] =
//     {
//         GL_NEVER,
//         GL_LESS,
//         GL_EQUAL,
//         GL_LEQUAL,
//         GL_GREATER,
//         GL_NOTEQUAL,
//         GL_GEQUAL,
//         GL_ALWAYS
//     };
// 
//     GLenum DXEnum::TextureOp[] =
//     {
//         GL_REPLACE,
//         GL_ADD,
//         GL_MODULATE,
//         GL_REPLACE,
//         GL_ADD,
//         GL_MODULATE
//     };
// 
//     GLenum DXEnum::TextureArg[] =
//     {
//         GL_PRIMARY_COLOR_EXT,
//         GL_TEXTURE,
//         GL_PREVIOUS_EXT,
//         GL_CONSTANT_EXT
//     };
// 
//     GLenum DXEnum::RenderParameter[] =
//     {
//         0,
//         GL_BLEND,
//         GL_DEPTH_TEST,
//         GL_TEXTURE_COMPARE_MODE,
//         GL_VERTEX_PROGRAM_POINT_SIZE,
//         GL_POINT_SPRITE
//     };
// 
//     GLenum DXEnum::RenderMode[] =
//     {
//         GL_FILL,
//         GL_LINE,
//         GL_POINT
//     };
// 
//     GLenum DXEnum::ShaderType[] =
//     {
//         GL_VERTEX_SHADER,
//         GL_TESS_CONTROL_SHADER,
//         GL_TESS_EVALUATION_SHADER,
//         GL_GEOMETRY_SHADER,
//         GL_FRAGMENT_SHADER
//     };
// 
//     GLenum DXEnum::AttachmentType[] =
//     {
//         GL_COLOR_ATTACHMENT0,
//         GL_COLOR_ATTACHMENT1,
//         GL_COLOR_ATTACHMENT2,
//         GL_COLOR_ATTACHMENT3,
//         GL_COLOR_ATTACHMENT4,
//         GL_COLOR_ATTACHMENT5,
//         GL_COLOR_ATTACHMENT6,
//         GL_COLOR_ATTACHMENT7,
//         GL_COLOR_ATTACHMENT8,
//         GL_COLOR_ATTACHMENT9,
//         GL_COLOR_ATTACHMENT10,
//         GL_COLOR_ATTACHMENT11,
//         GL_COLOR_ATTACHMENT12,
//         GL_COLOR_ATTACHMENT13,
//         GL_COLOR_ATTACHMENT14,
//         GL_COLOR_ATTACHMENT15,
//         GL_DEPTH_ATTACHMENT,
//         GL_STENCIL_ATTACHMENT
//     };
// 
//     GLenum DXEnum::TextureType[] = 
//     {
//         GL_TEXTURE_2D,
//         GL_TEXTURE_CUBE_MAP
//     };
// 
//     unsigned long DXEnum::BufferFlags(unsigned long flags)
//     {
//         if(flags & BUF_STREAM)
//             return GL_STREAM_DRAW;
// 
//         return (flags & BUF_DYNAMIC ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
//     }
// 
//     unsigned long DXEnum::LockBitsFlags(unsigned long flags)
//     {
//         unsigned long lockFlags = 0;
//         if (flags & LOCK_READONLY)  lockFlags |= GL_MAP_READ_BIT;
//         if (flags & LOCK_WRITEONLY) lockFlags |= GL_MAP_WRITE_BIT;
//         if (flags & LOCK_UNSYNCHRONOUS) lockFlags |= GL_MAP_UNSYNCHRONIZED_BIT;
//         return lockFlags;
//     }
// 
// 
//     unsigned long DXEnum::LockFlags(unsigned long flags)
//     {
//         unsigned long lockFlags = GL_READ_WRITE;
//         if (flags & LOCK_READONLY)  lockFlags = GL_READ_ONLY;
//         if (flags & LOCK_WRITEONLY) lockFlags = GL_WRITE_ONLY;
// 
//         return lockFlags;
//     }
// 
//     GLenum DXEnum::Get(TMatrixType value)
//     {
//         return MatrixType[value];
//     }
// 
//     std::string DXEnum::GetName(TMatrixType value)
//     {
//         return MatrixName[value];
//     }
// 
//     DXEnum::TPixelFmt DXEnum::Get(TPixelFormat value)
//     {
//         return PixelFormat[value];
//     }
// 
//     GLenum DXEnum::Get(TBlend value)
//     {
//         return Blend[value];
//     }
// 
//     GLenum DXEnum::Get(TDepth value)
//     {
//         return Depth[value];
//     }
// 
//     GLenum DXEnum::Get(TTextureOp value)
//     {
//         return TextureOp[value];
//     }
// 
//     GLenum DXEnum::Get(TTextureArg value)
//     {
//         return TextureArg[value];
//     }
// 
//     GLenum DXEnum::Get(TRenderParameter value)
//     {
//         if(value > 5)
//             return RenderParameter[0];
//         return RenderParameter[value];
//     }
// 
//     GLenum DXEnum::Get(TRenderMode value)
//     {
//         return RenderMode[value];
//     }
// 
//     GLenum DXEnum::Get(TShaderType value)
//     {
//         return ShaderType[value];
//     }
// 
//     GLenum DXEnum::GetAttachment(a_uint32 value)
//     {
//         return AttachmentType[value];
//     }
// 
//     GLenum DXEnum::Get(TTextureType value)
//     {
//         return TextureType[value];
//     }

    D3D_PRIMITIVE_TOPOLOGY DXEnum::PrimitiveType[] =
    {

        D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
        D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
        D3D_PRIMITIVE_TOPOLOGY_UNDEFINED, //triangle_fan
        D3D_PRIMITIVE_TOPOLOGY_LINELIST,
        D3D_PRIMITIVE_TOPOLOGY_LINESTRIP,
        D3D_PRIMITIVE_TOPOLOGY_POINTLIST,
        D3D_PRIMITIVE_TOPOLOGY_UNDEFINED //PATHLIST not handle :'(
        /*
        D3DPT_TRIANGLELIST,
        D3DPT_TRIANGLESTRIP,
        D3DPT_TRIANGLEFAN,
        D3DPT_LINELIST,
        D3DPT_LINESTRIP,
        D3DPT_POINTLIST*/
    };



    D3D_PRIMITIVE_TOPOLOGY DXEnum::Get( TPrimitiveType value )
    {
        return PrimitiveType[value];
    }

}