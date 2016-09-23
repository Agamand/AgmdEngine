/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifdef __DEBUG

#ifndef DEBUGNEW_H
#define DEBUGNEW_H
#include <Debug/MemoryMgr.h>

inline void* operator new(std::size_t size, const char* file, int line)
{
    return AgmdUtilities::MemoryMgr::Instance().Allocate(size, file, line, false);
}


inline void* operator new[](std::size_t size, const char* file, int line)
{
    return AgmdUtilities::MemoryMgr::Instance().Allocate(size, file, line, true);
}

inline void operator delete(void* ptr) throw()
{
    AgmdUtilities::MemoryMgr::Instance().Free(ptr, false);
}

inline void operator delete[](void* ptr) throw()
{
    AgmdUtilities::MemoryMgr::Instance().Free(ptr, true);
}

#ifndef __BORLANDC__

inline void operator delete(void* ptr, const char* file, int line) throw()
{
    AgmdUtilities::MemoryMgr::Instance().NextDelete(file, line);
    AgmdUtilities::MemoryMgr::Instance().Free(ptr, false);
}

inline void operator delete[](void* ptr, const char* file, int line) throw()
{
    AgmdUtilities::MemoryMgr::Instance().NextDelete(file, line);
    AgmdUtilities::MemoryMgr::Instance().Free(ptr, true);
}
#endif // __BORLANDC__


#endif // DEBUGNEW_H

#ifndef new
    #define new    new(__FILE__, __LINE__)
    #define delete Agmd::MemoryMgr::Instance().NextDelete(__FILE__, __LINE__), delete
#endif

#endif // _DEBUG
