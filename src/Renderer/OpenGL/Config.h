/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _OPENGL_EXPORT_H_
#define _OPENGL_EXPORT_H_

namespace Agmd
{
    
    #ifndef __GNUC__
    #    define __DLL_IMPORT__    __declspec(dllimport)
    #    define __DLL_EXPORT__    __declspec(dllexport)
    #else
    #    define __DLL_IMPORT__    __attribute__((dllimport)) extern
    #    define __DLL_EXPORT__    __attribute__((dllexport)) extern
    #endif 

    #ifdef OPENGL_EXPORTS
    #   define OPENGL_EXPORT __DLL_EXPORT__
    #else
    #   define OPENGL_EXPORT __DLL_IMPORT__
    #endif

    #ifdef _MSC_VER
    #   pragma warning(disable : 4251)
    #   pragma warning(disable : 4661)
    #endif

}
#endif /* _OPENGL_EXPORT_H_ */
