//==========================================================
//==========================================================

#ifdef _DEBUG

#ifndef DEBUGNEW_H
#define DEBUGNEW_H

#include <Debug/MemoryMgr.h>

inline void* operator new(std::size_t Size, const char* File, int Line)
{
    return Agmd::MemoryMgr::Instance().Allocate(Size, File, Line, false);
}


inline void* operator new[](std::size_t Size, const char* File, int Line)
{
    return Agmd::MemoryMgr::Instance().Allocate(Size, File, Line, true);
}

inline void operator delete(void* Ptr) throw()
{
    Agmd::MemoryMgr::Instance().Free(Ptr, false);
}

inline void operator delete[](void* Ptr) throw()
{
    Agmd::MemoryMgr::Instance().Free(Ptr, true);
}

#ifndef __BORLANDC__

inline void operator delete(void* Ptr, const char* File, int Line) throw()
{
    Agmd::MemoryMgr::Instance().NextDelete(File, Line);
    Agmd::MemoryMgr::Instance().Free(Ptr, false);
}

inline void operator delete[](void* Ptr, const char* File, int Line) throw()
{
    Agmd::MemoryMgr::Instance().NextDelete(File, Line);
    Agmd::MemoryMgr::Instance().Free(Ptr, true);
}
#endif // __BORLANDC__


#endif // DEBUGNEW_H

#ifndef new
    #define new    new(__FILE__, __LINE__)
    #define delete Agmd::MemoryMgr::Instance().NextDelete(__FILE__, __LINE__), delete
#endif

#endif // _DEBUG

