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

	#define MAX_APIMATRIX 10
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

	enum TTextureUnit
	{
		TEXTURE_UNIT_0  = 1 << 0,
		TEXTURE_UNIT_1  = 1 << 1,
		TEXTURE_UNIT_2  = 1 << 2,
		TEXTURE_UNIT_3  = 1 << 3,
		TEXTURE_UNIT_4  = 1 << 4,
		TEXTURE_UNIT_5  = 1 << 5,
		TEXTURE_UNIT_6  = 1 << 6,
		TEXTURE_UNIT_7  = 1 << 7,
		TEXTURE_UNIT_8  = 1 << 8,
		TEXTURE_UNIT_9  = 1 << 9,
		TEXTURE_UNIT_10 = 1 << 10,
		TEXTURE_UNIT_11 = 1 << 11,
		TEXTURE_UNIT_12 = 1 << 12,
		TEXTURE_UNIT_13 = 1 << 13,
		TEXTURE_UNIT_14 = 1 << 14,
		TEXTURE_UNIT_15 = 1 << 15,
		TEXTURE_UNIT_16 = 1 << 16,
		TEXTURE_UNIT_17 = 1 << 17,
		TEXTURE_UNIT_18 = 1 << 18,
		TEXTURE_UNIT_19 = 1 << 19,
		TEXTURE_UNIT_20 = 1 << 20,
		TEXTURE_UNIT_21 = 1 << 21,
		TEXTURE_UNIT_22 = 1 << 22,
		TEXTURE_UNIT_23 = 1 << 23,
		TEXTURE_UNIT_24 = 1 << 24,
		TEXTURE_UNIT_25 = 1 << 25,
		TEXTURE_UNIT_26 = 1 << 26,
		TEXTURE_UNIT_27 = 1 << 27,
		TEXTURE_UNIT_28 = 1 << 28,
		TEXTURE_UNIT_29 = 1 << 29,
		TEXTURE_UNIT_30 = 1 << 30,
		TEXTURE_UNIT_31 = 1 << 31
	};

	enum TComponent
	{
	
	};

	#define MAX_TEXTUREUNIT 32

}


#endif // ENUMS_H