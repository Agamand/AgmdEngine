
#include <Debug\MemoryMgr.h>
#include <Debug\Exception.h>
#include <iostream>
#include <iomanip>
#include <assert.h>

namespace AgmdUtilities
{
    MemoryMgr* MemoryMgr::_Instance = NULL;

    MemoryMgr::MemoryMgr() : m_File("alloc.log")
    {
        if(!m_File)
            throw LoadingFailed("alloc.log","Loading fail");

        m_File << "  =============================================" << std::endl;
        m_File << "  AgmdEngine v0.1 Alpha - Memory leak tracker " << std::endl;
        m_File << "  =============================================" << std::endl << std::endl;
    }

    MemoryMgr::~MemoryMgr()
    {
        if(m_memBlock.empty())
        {
            m_File << "  =============================================" << std::endl;
            m_File << "  No leak detected ! " << std::endl;
            m_File << "  =============================================" << std::endl << std::endl;
        }
        else
        {
            m_File << "  =============================================" << std::endl;
            m_File << "   "<< m_memBlock.size() <<" leak detected !   " << std::endl;
            m_File << "  =============================================" << std::endl << std::endl;
        }
    }

    MemoryMgr& MemoryMgr::Instance()
    {
        if(!_Instance)
            _Instance = new MemoryMgr();

        assert(_Instance != NULL);
        return *_Instance;
    }
    void* MemoryMgr::Allocate(std::size_t size, File file, uint32 line, bool isArray)
    {
        void *ptr = malloc(size);
        assert(ptr != NULL);
        memBlock block(size,file,line,isArray);
        m_memBlock[ptr] = block; 
        m_File << "++ Alloc    | 0x" << ptr
           << " | " << static_cast<int>(block.size) << " octets"
           << " | " << std::endl;
        return ptr;
    }
    void MemoryMgr::Free(void *ptr, bool isArray)
    {
        memBlockMap::iterator It = m_memBlock.find(ptr);

        if (It == m_memBlock.end())
        {
            free(ptr);
            return;
        }

        /*if (It->second.isArray != isArray)
        {
            throw BadDelete(ptr, It->second.file.Filename(), It->second.line, !isArray);
        }*/

        m_File << "-- Unalloc | 0x" << ptr
               << " | " << std::setw(7) << std::setfill(' ') << static_cast<int>(It->second.size) << " octets"
               << " | " << m_DeleteStack.top().file.Filename() << " (" << m_DeleteStack.top().line << ")" << std::endl;
        m_memBlock.erase(It);
        m_DeleteStack.pop();

        free(ptr);
    }
    void MemoryMgr::NextDelete(File file, uint32 line)
    {
        memBlock _delete;
        _delete.file = file;
        _delete.line = line;

        m_DeleteStack.push(_delete);
    }


}