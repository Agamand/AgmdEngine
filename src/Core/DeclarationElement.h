#ifndef DECLARATIONELEMENT_H
#define DECLARATIONELEMENT_H


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
		ELT_USAGE_TANGENT
    };

    enum TElementType
    {
        ELT_TYPE_FLOAT1,
        ELT_TYPE_FLOAT2,
        ELT_TYPE_FLOAT3,
        ELT_TYPE_FLOAT4,
        ELT_TYPE_COLOR
    };

    struct TDeclarationElement
    {
        unsigned int  stream;
        TElementUsage usage;
        TElementType  dataType;
    };


}


#endif // DECLARATIONELEMENT_H
