/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/


#ifndef FILE_H
#define FILE_H

#include <string>


namespace AgmdUtilities
{
    class File
    {
    public :

        File(const std::string& name = "");
        File(const char* name);
        bool Exists() const;
        const std::string& Fullname() const;
        std::string Filename() const;
        std::string ShortFilename() const;
        std::string Extension() const;
        std::string Path() const;

    private :

        std::string m_Name;
    };
}


#endif // FILE_H
