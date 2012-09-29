#ifndef PLUGIN_H
#define PLUGIN_H

#include <Debug/Exception.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


namespace AgmdUtilities
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