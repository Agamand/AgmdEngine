/*
============================================================================
AgmdEngine - GameEngine
Author : 
Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
Jean-Vincent Lamberti (https://github.com/kinroux)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _EXPORTGAMEENGINE_H_
#define _EXPORTGAMEENGINE_H_

namespace Agmd
{
    
    #ifndef __GNUC__
    #    define __DLL_IMPORT__    __declspec(dllimport)
    #    define __DLL_EXPORT__    __declspec(dllexport)
    #else
    #    define __DLL_IMPORT__    __attribute__((dllimport)) extern
    #    define __DLL_EXPORT__    __attribute__((dllexport)) extern
    #endif 

    #ifdef GAMEENGINE_EXPORTS
    #   define GAMEENGINE_EXPORT __DLL_EXPORT__
    #else
    #   define GAMEENGINE_EXPORT __DLL_IMPORT__
    #endif

    #ifdef _MSC_VER
    #   pragma warning(disable : 4251)
    #   pragma warning(disable : 4661)
    #endif

}
#endif /* _EXPORTGAMEENGINE_H_ */
