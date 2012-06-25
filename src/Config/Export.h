//==========================================================
//==========================================================


#ifndef EXPORT_H
#define EXPORT_H

namespace Agmd
{
    #ifdef AGMDENGINE_EXPORTS
    #   define AGMD_EXPORT __declspec(dllexport)
    #else
    #   define AGMD_EXPORT __declspec(dllimport)
    #endif

    #ifdef _MSC_VER
    #   pragma warning(disable : 4251)
    #   pragma warning(disable : 4661)
    #endif
}
#endif // EXPORT_H
