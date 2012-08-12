#ifndef PLUGIN_H
#define PLUGIN_H

#include <Debug/Exception.h>
#include <windows.h>


namespace Agmd
{
    class Plugin
    {
    public:
        Plugin(const std::string& Filename);
        ~Plugin();
    private :
        typedef void (*PtrFunc)();

        HMODULE m_Library;
    };

}


#endif // PLUGIN_H