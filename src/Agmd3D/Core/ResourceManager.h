/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <Core/Resource.h>
#include <Utilities/Singleton.h>
#include <Debug/Logger.h>
#include <map>
#include <string>

using namespace AgmdUtilities;

namespace Agmd
{
    class AGMD3D_EXPORT ResourceManager : public Singleton<ResourceManager>
    {
        MAKE_SINGLETON(ResourceManager)

    public :

        template <class T>
        T* Get(const std::string& name) const;

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
