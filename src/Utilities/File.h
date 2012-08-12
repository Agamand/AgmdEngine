
#ifndef FILE_H
#define FILE_H

#include <Config/Export.h>
#include <string>


namespace Agmd
{
    class AGMD_EXPORT File
    {
    public :

        File(const std::string& name = "");
        File(const char* name);
        bool Exists() const;
        const std::string& Fullname() const;
        std::string Filename() const;
        std::string ShortFilename() const;
        std::string Extension() const;

    private :

        std::string m_Name;
    };

}


#endif // FILE_H