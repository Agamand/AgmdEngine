#ifndef ENUMS_H
#define ENUMS_H

namespace Agmd
{
	enum TMouseState
	{
		MOUSE_NONE		= 0x0,
		MOUSE_LEFT		= 0x1,
		MOUSE_RIGHT		= 0x2,
		MOUSE_MIDDLE	= 0x10
	};

    enum TPrimitiveType
    {
        PT_TRIANGLELIST,
        PT_TRIANGLESTRIP,
        PT_TRIANGLEFAN,
        PT_LINELIST, 
        PT_LINESTRIP,
        PT_POINTLIST,
		PT_PATCHLIST
    };

	enum TTextureType
	{
		TEXTURE_2D,
		TEXTURE_CUBE
	};

	enum
    {
        BUF_STATIC  = 1 << 0,
        BUF_DYNAMIC = 1 << 1
    };

    enum
    {
        LOCK_READONLY  = 1 << 0,
        LOCK_WRITEONLY = 1 << 1
    };

    enum TMatrixType
    {
        MAT_MODEL,
		MAT_VIEW,
        MAT_PROJECTION,
        MAT_TEXTURE_0,
        MAT_TEXTURE_1,
        MAT_TEXTURE_2,
        MAT_TEXTURE_3,
		MAT_NORMAL,
		MAT_POSITION,
		MAT_ROTATION
    };

    enum TPixelFormat
    {
        PXF_L8,
        PXF_A8L8,
        PXF_A1R5G5B5,
	    PXF_A4R4G4B4,
	    PXF_R8G8B8,
	    PXF_A8R8G8B8,
        PXF_DXTC1,
        PXF_DXTC3,
        PXF_DXTC5,
		PXF_DEPTH
    };

    enum
    {
        TEX_NOMIPMAP = 1 << 0
    };

    enum TCapability
    {
        CAP_HW_MIPMAPPING,
        CAP_DXT_COMPRESSION,
        CAP_TEX_NON_POWER_2,
		CAP_TESSELATION_SHADER
    };

    enum TBlend
    {
        BLEND_SRCALPHA,
        BLEND_INVSRCALPHA,
        BLEND_DESTALPHA,
        BLEND_INVDESTALPHA,
        BLEND_SRCCOLOR,
        BLEND_INVSRCCOLOR,
        BLEND_DESTCOLOR,
        BLEND_INVDESTCOLOR,
        BLEND_ONE,
        BLEND_ZERO
    };

    enum TTextureOp
    {
        TXO_COLOR_FIRSTARG,
        TXO_COLOR_ADD,
        TXO_COLOR_MODULATE,
        TXO_ALPHA_FIRSTARG,
        TXO_ALPHA_ADD,
        TXO_ALPHA_MODULATE
    };

    enum TTextureArg
    {
        TXA_DIFFUSE,
        TXA_TEXTURE,
        TXA_PREVIOUS,
        TXA_CONSTANT
    };

    enum TAlign
    {
        ALIGN_LEFT    = 1 << 0,
        ALIGN_HCENTER = 1 << 1,
        ALIGN_RIGHT   = 1 << 2, 
        ALIGN_TOP     = 1 << 3,
        ALIGN_VCENTER = 1 << 4,
        ALIGN_BOTTOM  = 1 << 5
    };

    enum TRenderParameter
    {
        RENDER_ZWRITE,
        RENDER_ALPHABLEND, 
		RENDER_TRANSPARENT,
		RENDER_CLIP_PLANE0,
		RENDER_CLIP_PLANE1,
		RENDER_CLIP_PLANE2,
		RENDER_CLIP_PLANE3,
		RENDER_CLIP_PLANE4,
		RENDER_CLIP_PLANE5,
		RENDER_TEXTURE0,
		RENDER_TEXTURE1,
		RENDER_TEXTURE2,
		RENDER_TEXTURE3,
		RENDER_TEXTURE4,
		RENDER_TEXTURE5
    };

    enum TShaderType
    {
        SHADER_VERTEX,
		SHADER_TESS_CONTROL,
		SHADER_TESS_EVALUATION,
		SHADER_GEOMETRY,
        SHADER_PIXEL
    };

	enum TRenderMode
	{
		MODE_FILL,
		MODE_LINE,
		MODE_POINT
	};

	enum TAttachment
	{
		COLOR_ATTACHMENT,
		DEPTH_ATTACHMENT = 16,
		STENCIL_ATTACHEMENT = 17
	};

	enum TComponent
	{
	
	};

	#define MAX_TEXTUREUNIT 32

}


#endif // ENUMS_H