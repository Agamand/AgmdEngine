/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _EXPORT_H_
#define _EXPORT_H_

namespace Agmd
{
#ifndef __GNUC__
#    define __DLL_IMPORT__    __declspec(dllimport)
#    define __DLL_EXPORT__    __declspec(dllexport)
#else
    #    define __DLL_IMPORT__    __attribute__((dllimport)) extern
    #    define __DLL_EXPORT__    __attribute__((dllexport)) extern
#endif 

#ifdef AGMD3D_EXPORTS
#   define AGMD3D_EXPORT __DLL_EXPORT__
#else
    #   define AGMD3D_EXPORT __DLL_IMPORT__
#endif

#ifdef _MSC_VER
#   pragma warning(disable : 4251)
#   pragma warning(disable : 4661)
#endif
}
#endif /* _EXPORT_H_ */
