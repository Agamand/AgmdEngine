/*
============================================================================
GLRender - Opengl Renderer specialization
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Renderer\OpenGL\GlEnums.h>
#include <gl\glext.h>

namespace Agmd
{
    GLenum RGLEnum::MatrixType[] =
    {
        GL_MODELVIEW,
        GL_PROJECTION,
        GL_TEXTURE,
        GL_TEXTURE,
        GL_TEXTURE,
        GL_TEXTURE
    };

    std::string  RGLEnum::MatrixName[] =
    {
        "u_matModel",
        "u_matView",
        "u_matProjection",
        "texture0Matrix",
        "texture1Matrix",
        "texture2Matrix",
        "texture3Matrix",
        "normalMatrix",
        "positionMatrix",
        "rotationMatrix"
    };

    RGLEnum::TPixelFmt RGLEnum::PixelFormat[] =
    {
        {GL_LUMINANCE,       GL_LUMINANCE8,                    GL_UNSIGNED_BYTE,              GL_RGBA},
        {GL_LUMINANCE_ALPHA, GL_LUMINANCE8_ALPHA8,             GL_UNSIGNED_BYTE,              GL_RGBA},
        {GL_BGRA,            GL_RGB5_A1,                       GL_UNSIGNED_SHORT_1_5_5_5_REV, GL_RGBA},
        {GL_BGRA,            GL_RGBA4,                         GL_UNSIGNED_SHORT_4_4_4_4_REV, GL_RGBA},
        {GL_BGR,             GL_RGB8,                          GL_UNSIGNED_BYTE,              GL_RGBA},
        {GL_BGRA,            GL_RGBA8,                         GL_UNSIGNED_BYTE,              GL_RGBA},
        {GL_BGR,             GL_COMPRESSED_RGBA_S3TC_DXT1_EXT, 0,                             GL_RGBA},
        {GL_BGRA,            GL_COMPRESSED_RGBA_S3TC_DXT3_EXT, 0,                             GL_RGBA},
        {GL_BGRA,            GL_COMPRESSED_RGBA_S3TC_DXT5_EXT, 0,                             GL_RGBA},
        {GL_BGRA,            GL_DEPTH_COMPONENT32,             GL_UNSIGNED_BYTE,              GL_DEPTH_COMPONENT},
        {GL_BGR,             GL_RGB16F,                        GL_UNSIGNED_BYTE,              GL_RGBA},
        {GL_BGR,             GL_RGB32F,                        GL_UNSIGNED_BYTE,              GL_RGBA}
    };

    GLenum RGLEnum::Blend[] =
    {
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA,
        GL_DST_ALPHA,
        GL_ONE_MINUS_DST_ALPHA,
        GL_SRC_COLOR,
        GL_ONE_MINUS_SRC_COLOR,
        GL_DST_COLOR,
        GL_ONE_MINUS_DST_COLOR,
        GL_ONE,
        GL_ZERO
    };

    GLenum RGLEnum::Depth[] =
    {
        GL_NEVER,
        GL_LESS,
        GL_EQUAL,
        GL_LEQUAL,
        GL_GREATER,
        GL_NOTEQUAL,
        GL_GEQUAL,
        GL_ALWAYS
    };

    GLenum RGLEnum::TextureOp[] =
    {
        GL_REPLACE,
        GL_ADD,
        GL_MODULATE,
        GL_REPLACE,
        GL_ADD,
        GL_MODULATE
    };

    GLenum RGLEnum::TextureArg[] =
    {
        GL_PRIMARY_COLOR_EXT,
        GL_TEXTURE,
        GL_PREVIOUS_EXT,
        GL_CONSTANT_EXT
    };

    GLenum RGLEnum::RenderParameter[] =
    {
        0,
        GL_BLEND,
        GL_DEPTH_TEST,
        GL_TEXTURE_COMPARE_MODE,
		GL_VERTEX_PROGRAM_POINT_SIZE,
		GL_POINT_SPRITE
    };

    GLenum RGLEnum::RenderMode[] =
    {
        GL_FILL,
        GL_LINE,
        GL_POINT
    };

    GLenum RGLEnum::ShaderType[] =
    {
        GL_VERTEX_SHADER,
        GL_TESS_CONTROL_SHADER,
        GL_TESS_EVALUATION_SHADER,
        GL_GEOMETRY_SHADER,
        GL_FRAGMENT_SHADER
    };

    GLenum RGLEnum::AttachmentType[] =
    {
        GL_COLOR_ATTACHMENT0,
        GL_COLOR_ATTACHMENT1,
        GL_COLOR_ATTACHMENT2,
        GL_COLOR_ATTACHMENT3,
        GL_COLOR_ATTACHMENT4,
        GL_COLOR_ATTACHMENT5,
        GL_COLOR_ATTACHMENT6,
        GL_COLOR_ATTACHMENT7,
        GL_COLOR_ATTACHMENT8,
        GL_COLOR_ATTACHMENT9,
        GL_COLOR_ATTACHMENT10,
        GL_COLOR_ATTACHMENT11,
        GL_COLOR_ATTACHMENT12,
        GL_COLOR_ATTACHMENT13,
        GL_COLOR_ATTACHMENT14,
        GL_COLOR_ATTACHMENT15,
        GL_DEPTH_ATTACHMENT,
        GL_STENCIL_ATTACHMENT
    };

    GLenum RGLEnum::TextureType[] = 
    {
        GL_TEXTURE_2D,
        GL_TEXTURE_CUBE_MAP
    };

    unsigned long RGLEnum::BufferFlags(unsigned long flags)
    {
        if(flags & BUF_STREAM)
            return GL_STREAM_DRAW;

        return (flags & BUF_DYNAMIC ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }

    unsigned long RGLEnum::LockBitsFlags(unsigned long flags)
    {
        unsigned long lockFlags = 0;
        if (flags & LOCK_READONLY)  lockFlags |= GL_MAP_READ_BIT;
        if (flags & LOCK_WRITEONLY) lockFlags |= GL_MAP_WRITE_BIT;
        if (flags & LOCK_UNSYNCHRONOUS) lockFlags |= GL_MAP_UNSYNCHRONIZED_BIT;
        return lockFlags;
    }


    unsigned long RGLEnum::LockFlags(unsigned long flags)
    {
        unsigned long lockFlags = GL_READ_WRITE;
        if (flags & LOCK_READONLY)  lockFlags = GL_READ_ONLY;
        if (flags & LOCK_WRITEONLY) lockFlags = GL_WRITE_ONLY;

        return lockFlags;
    }

    GLenum RGLEnum::Get(TMatrixType value)
    {
        return MatrixType[value];
    }

    std::string RGLEnum::GetName(TMatrixType value)
    {
        return MatrixName[value];
    }

    RGLEnum::TPixelFmt RGLEnum::Get(TPixelFormat value)
    {
        return PixelFormat[value];
    }

    GLenum RGLEnum::Get(TBlend value)
    {
        return Blend[value];
    }

    GLenum RGLEnum::Get(TDepth value)
    {
        return Depth[value];
    }

    GLenum RGLEnum::Get(TTextureOp value)
    {
        return TextureOp[value];
    }

    GLenum RGLEnum::Get(TTextureArg value)
    {
        return TextureArg[value];
    }

    GLenum RGLEnum::Get(TRenderParameter value)
    {
        if(value > 5)
            return RenderParameter[0];
        return RenderParameter[value];
    }

    GLenum RGLEnum::Get(TRenderMode value)
    {
        return RenderMode[value];
    }

    GLenum RGLEnum::Get(TShaderType value)
    {
        return ShaderType[value];
    }

    GLenum RGLEnum::GetAttachment(a_uint32 value)
    {
        return AttachmentType[value];
    }

    GLenum RGLEnum::Get(TTextureType value)
    {
        return TextureType[value];
    }
}