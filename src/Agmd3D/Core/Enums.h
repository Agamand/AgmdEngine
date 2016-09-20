/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef ENUMS_H
#define ENUMS_H

namespace Agmd
{
    enum TMouseState
    {
        MOUSE_NONE        = 0x0,
        MOUSE_LEFT        = 0x1,
        MOUSE_RIGHT        = 0x2,
        MOUSE_MIDDLE    = 0x10
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
        BUF_DYNAMIC = 1 << 1,
        BUF_STREAM  = 1 << 2
    };

    enum
    {
        LOCK_READONLY       = 1 << 0,
        LOCK_WRITEONLY      = 1 << 1,
        LOCK_UNSYNCHRONOUS  = 1 << 2,
        LOCK_SYNC_WAIT      = 1 << 3
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
        PXF_DEPTH,
        PXF_R16G16B16,
        PXF_R32G32B32
    };

    enum
    {
        TEX_NOMIPMAP = 1 << 0,
        TEX_WRAP_CLAMP = 1 << 1,
        TEX_USE_FILTER = 1 << 2
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

    enum TDepth
    {
        DEPTH_NEVER,
        DEPTH_LESS,
        DEPTH_EQUAL,
        DEPTH_LEQUAL,
        DEPTH_GREATER,
        DEPTH_NOTEQUAL,
        DEPTH_GEQUAL,
        DEPTH_ALWAYS
    };

    enum TClear
    {
        CLEAR_COLOR     = 0x01,
        CLEAR_DEPTH     = 0x02,
        CLEAR_STENCIL   = 0x04,
        CLEAR_ALL       = CLEAR_COLOR | CLEAR_DEPTH | CLEAR_STENCIL
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
        RENDER_ZTEST,
        RENDER_COMPARE_MODE,
        RENDER_POINTSIZE_SHADER,
        RENDER_POINTSPRITE,
        RENDER_TRANSPARENT,
        RENDER_RENDERING
        
    };
    #define TSHADERTYPE_MAX 5
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
        STENCIL_ATTACHMENT = 17,
        MAX_ATTACHMENT
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

    #define MAX_RENDERPASS 13

    enum TRenderPass
    {
        RENDERPASS_ZBUFFER,
        RENDERPASS_DIFFUSE,
        RENDERPASS_POINT_SHADOW_CAST,
        RENDERPASS_DIRECTIONNAL_SHADOW_CAST,
        RENDERPASS_SPOT_SHADOW_CAST,
        RENDERPASS_POINT_LIGHTING,
        RENDERPASS_DIRECTIONNAL_LIGHTING,
        RENDERPASS_SPOT_LIGHTING,
        RENDERPASS_POINT_LIGHTING_WITH_SHADOW,
        RENDERPASS_DIRECTIONNAL_LIGHTING_WITH_SHADOW,
        RENDERPASS_SPOT_LIGHTING_WITH_SHADOW,
        RENDERPASS_DEFERRED,
        RENDERPASS_FORWARD_LIGHTING
    };

    enum TUniformBind
    {
        UNIFORM_CAMERA3D_BIND,
        UNIFORM_LIGHT_BIND,
        UNIFORM_CAMERA2D_BIND
    };

    enum TCamera
    {
        CAMERA_3D,
        CAMERA_2D
    };

    enum TComponent
    {
    
    };

    #define MAX_TEXTUREUNIT 32

}


#endif // ENUMS_H