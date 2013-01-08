#ifndef _AGMDDEFINES_H_
#define _AGMDDEFINES_H_

#define ENGINE_REV 3
#define ENGINE_NAME "AgmdEngine"
#define ENGINE_STATE "Alpha"

#define AGMD_MAJOR 0
#define AGMD_MINOR 2


#if _WIN32 || _WIN64
#define __WIN_PLATFORM__
#endif




typedef long long			int64;
typedef int					int32;
typedef short int			int16;
typedef char				int8;
typedef unsigned long long  uint64;
typedef unsigned int		uint32;
typedef unsigned short		uint16;
typedef unsigned char		uint8;

//typedef unsigned char       ubyte;
//typedef char                byte;


#endif /* _AGMDDEFINES_H_ */