#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <Core/Resource.h>
#include <Utilities/Singleton.h>
#include <map>
#include <string>


namespace Agmd
{

    class AGMD_EXPORT ResourceManager : public Singleton<ResourceManager>
    {
    MAKE_SINGLETON(ResourceManager)

    public :

        template <class T> T* Get(const std::string& name) const;

        void Add(const std::string& Name, Resource* resource);

        void Remove(const std::string& name);

    private :

        ResourceManager();

        ~ResourceManager();

        typedef std::map<std::string, Resource*> TResourcesMap;

        TResourcesMap m_Resources;
    };

    #include "ResourceManager.inl"

}


#endif // RESOURCEMANAGER_H
