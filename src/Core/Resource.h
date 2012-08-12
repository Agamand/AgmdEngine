#ifndef RESOURCE_H
#define RESOURCE_H

#include <Config/Export.h>
#include <string>


namespace Agmd
{
    class AGMD_EXPORT Resource
    {
    public :

        Resource();

        virtual ~Resource() = 0;

        const std::string& GetName() const;

        void AddRef();

        int Release();

    private :

        friend class ResourceManager;

        Resource(Resource&);
        void operator =(Resource&);

        std::string m_Name; 
        int         m_RefCount;
    };

}


#endif // RESOURCE_H
