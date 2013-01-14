/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef MEMORYMGR_H
#define MEMORYMGR_H
#include <Utilities\File.h>
#include <AgmdDefines.h>
#include <cstdlib>
#include <map>
#include <stack>
#include <fstream>


namespace AgmdUtilities
{    
    class MemoryMgr
    {
    public:
        void* Allocate(std::size_t size, File file, uint32 line, bool isArray);
        void Free(void *ptr, bool isArray);
        void NextDelete(File file, uint32 line);

        static MemoryMgr& Instance();

    private:
        struct memBlock
        {
            memBlock() : size(0), line(0), isArray(false) {}
            memBlock(std::size_t _size,File _file, uint32 _line, bool _isArray) : size(_size),file(_file), line(_line), isArray(_isArray) {}
            memBlock(uint32 _line, bool _isArray) : size(0), line(_line), isArray(_isArray) {}
            std::size_t size;
            File file;
            uint32 line;
            bool isArray;
        };
        typedef std::map<void*, memBlock> memBlockMap;

        MemoryMgr();
        ~MemoryMgr();

        static MemoryMgr* _Instance;
        std::map<void*,memBlock> m_memBlock;
        std::ofstream m_File;
        std::stack<memBlock> m_DeleteStack;
    };
    
}

#endif