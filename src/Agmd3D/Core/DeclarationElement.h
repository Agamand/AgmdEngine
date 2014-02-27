/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef DECLARATIONELEMENT_H
#define DECLARATIONELEMENT_H
#include <CommonDefines.h>

namespace Agmd
{
    enum TElementUsage
    {
        ELT_USAGE_POSITION,
        ELT_USAGE_NORMAL, 
        ELT_USAGE_DIFFUSE,
        ELT_USAGE_TEXCOORD0,
        ELT_USAGE_TEXCOORD1, 
        ELT_USAGE_TEXCOORD2,
        ELT_USAGE_TEXCOORD3,
        ELT_USAGE_TANGENT,
        ELT_USAGE_BONE_WEIGHT,
        ELT_USAGE_BONE_INDEX,
        ELT_USAGE_BONE_COUNT
    };

    enum TElementType
    {
        ELT_TYPE_FLOAT1,
        ELT_TYPE_FLOAT2,
        ELT_TYPE_FLOAT3,
        ELT_TYPE_FLOAT4,
        ELT_TYPE_COLOR,
        ELT_TYPE_INT,
    };

    struct TDeclarationElement
    {
        a_uint32 stream;
        a_uint32 usage;
        TElementType  dataType;
    };


}


#endif // DECLARATIONELEMENT_H
