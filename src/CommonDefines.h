/*
============================================================================
AgmdEngine Define
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _COMMONDEFINES_H_
#define _COMMOMDEFINES_H_

#define ENGINE_REV      3
#define ENGINE_NAME     L"AgmdEngine"
#define ENGINE_STATE    "Alpha"

#define AGMD_MAJOR      0
#define AGMD_MINOR      2

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#if _WIN32 || _WIN64
#define __WIN_PLATFORM__
#endif
#define _DISABLE_WARNING_
#ifdef _DISABLE_WARNING_
#define _DEPRECATED_(name) name
#else
#ifdef GCC
#define _DEPRECATED_(name) __attribute__((deprecated)) name
#else
#define _DEPRECATED_(name) _CRT_DEPRECATE_TEXT("This function \"" #name "\" is deprecated, you may not use it !") name
#endif
#endif


typedef long long           a_int64;
typedef int                 a_int32;
typedef short int           a_int16;
typedef char                a_int8;
typedef unsigned long long  a_uint64;
typedef unsigned int        a_uint32;
typedef unsigned short      a_uint16;
typedef unsigned char       a_uint8;
typedef float				a_float;
typedef double				a_double;
typedef wchar_t				a_char;

#endif /* _COMMOMDEFINES_H_ */