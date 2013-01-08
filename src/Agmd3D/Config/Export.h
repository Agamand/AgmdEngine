#ifndef EXPORT_H
#define EXPORT_H

namespace Agmd
{
	
	#ifndef __GNUC__
	#	define __DLL_IMPORT__	__declspec(dllimport)
	#	define __DLL_EXPORT__	__declspec(dllexport)
	#else
	#	define __DLL_IMPORT__	__attribute__((dllimport)) extern
	#	define __DLL_EXPORT__	__attribute__((dllexport)) extern
	#endif 

    #ifdef AGMDENGINE_EXPORTS
    #   define AGMD_EXPORT __DLL_EXPORT__
    #else
    #   define AGMD_EXPORT __DLL_IMPORT__


    #endif

    #ifdef _MSC_VER
    #   pragma warning(disable : 4251)
    #   pragma warning(disable : 4661)
    #endif
}
#endif // EXPORT_H
