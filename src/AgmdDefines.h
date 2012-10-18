#ifndef AGMDDEFINES_H
#define AGMDDEFINES_H

#define ENGINE_REV 1
#define ENGINE_NAME "AgmdEngine"
#define ENGINE_STATE "Alpha"



#if _WIN32 || _WIN64
#define __WIN_PLATFORM__
#endif




typedef long long  int64;
typedef int       int32;
typedef short int    int16;
typedef char      int8;
typedef unsigned long long  uint64;
typedef unsigned int       uint32;
typedef unsigned short     uint16;
typedef unsigned char      uint8;


#endif