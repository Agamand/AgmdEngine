#ifndef PIXELUTILS_H
#define PIXELUTILS_H

#include <Agmd3D/Core/Enums.h>
#include <Debug/Exception.h>
#include <string>

using namespace Agmd;


namespace AgmdUtilities
{
    inline unsigned int GetBytesPerPixel(TPixelFormat format)
    {
        switch (format)
        {
            case PXF_L8 :       return 1;
            case PXF_A8L8 :     return 2;
            case PXF_A1R5G5B5 : return 2;
            case PXF_A4R4G4B4 : return 2;
            case PXF_R8G8B8 :   return 3;
            case PXF_A8R8G8B8 : return 4;
            case PXF_DXTC1 :    return 1;
            case PXF_DXTC3 :    return 2;
            case PXF_DXTC5 :    return 2;
			case PXF_DEPTH :	return 4;
            case PXF_R16G16B16: return 6;
            case PXF_R32G32B32: return 12;
            default :           return 0;
        }
    }

    inline std::string FormatToString(TPixelFormat format)
    {
        switch (format)
        {
            case PXF_L8 :       return "PXF_L8";
            case PXF_A8L8 :     return "PXF_A8L8";
            case PXF_A1R5G5B5 : return "PXF_A1R5G5B5";
            case PXF_A4R4G4B4 : return "PXF_A4R4G4B4";
            case PXF_R8G8B8 :   return "PXF_R8G8B8";
            case PXF_A8R8G8B8 : return "PXF_A8R8G8B8";
            case PXF_DXTC1 :    return "PXF_DXTC1";
            case PXF_DXTC3 :    return "PXF_DXTC3";
            case PXF_DXTC5 :    return "PXF_DXTC5";
            default :           return "Format inconnu";
        }
    }

    inline bool FormatCompressed(TPixelFormat format)
    {
        switch (format)
        {
            case PXF_DXTC1 :
            case PXF_DXTC3 :
            case PXF_DXTC5 :
                return true;

            default :
                return false;
        }
    }

    inline int GetNbMipLevels(int width, int height)
    {
        int count = 0;

        while ((width > 1) || (height > 1))
        {
            if (width > 1)  width  /= 2;
            if (height > 1) height /= 2;
            ++count;
        }

        return count;
    }

    template <TPixelFormat srcFmt, TPixelFormat destFmt>
    inline void ConvertPixel(const unsigned char* src, unsigned char* dest)
    {
        throw Unsupported(std::string("Conversion software de format de pixel (") +
                           FormatToString(srcFmt) +
                           " -> " +
                           FormatToString(destFmt) +
                           ")");
    }

    #include <Utilities/ConvertPixel.inl>


    inline void ConvertPixel(TPixelFormat srcFmt, const unsigned char* src, TPixelFormat destFmt, unsigned char* dest)
    {
        #define CONVERSIONS_FOR(Fmt) \
            case Fmt : \
            { \
                switch (destFmt) \
                { \
                    case PXF_L8 :       ConvertPixel<Fmt, PXF_L8>(src, dest);       break; \
                    case PXF_A8L8 :     ConvertPixel<Fmt, PXF_A8L8>(src, dest);     break; \
                    case PXF_A1R5G5B5 : ConvertPixel<Fmt, PXF_A1R5G5B5>(src, dest); break; \
                    case PXF_A4R4G4B4 : ConvertPixel<Fmt, PXF_A4R4G4B4>(src, dest); break; \
                    case PXF_R8G8B8 :   ConvertPixel<Fmt, PXF_R8G8B8>(src, dest);   break; \
                    case PXF_A8R8G8B8 : ConvertPixel<Fmt, PXF_A8R8G8B8>(src, dest); break; \
                    case PXF_DXTC1 :    ConvertPixel<Fmt, PXF_DXTC1>(src, dest);    break; \
                    case PXF_DXTC3 :    ConvertPixel<Fmt, PXF_DXTC3>(src, dest);    break; \
                    case PXF_DXTC5 :    ConvertPixel<Fmt, PXF_DXTC5>(src, dest);    break; \
                } \
                break; \
            }

        switch (srcFmt)
        {
            CONVERSIONS_FOR(PXF_L8)
            CONVERSIONS_FOR(PXF_A8L8)
            CONVERSIONS_FOR(PXF_A1R5G5B5)
            CONVERSIONS_FOR(PXF_A4R4G4B4)
            CONVERSIONS_FOR(PXF_R8G8B8)
            CONVERSIONS_FOR(PXF_A8R8G8B8)
            CONVERSIONS_FOR(PXF_DXTC1)
            CONVERSIONS_FOR(PXF_DXTC3)
            CONVERSIONS_FOR(PXF_DXTC5)
        }

        #undef CONVERIONS_FOR
    }

}


#endif //PIXELUTILS_H
