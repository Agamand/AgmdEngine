#include <Core/ResourceManager.h>
#include <Debug/Logger.h>
#include <Debug/Exception.h>
#include <Debug/New.h>


SINGLETON_IMPL(Agmd::ResourceManager);

namespace Agmd
{

	

	ResourceManager::ResourceManager()
	{}

	ResourceManager::~ResourceManager()
	{
		if (!m_Resources.empty())
		{
			Logger::Log(LOGNORMAL,"** warning ** Des ressources n'ont pas été libérées :");

			for (TResourcesMap::const_iterator i = m_Resources.begin(); i != m_Resources.end(); ++i)
			{
				Logger::Log(LOGNORMAL," - %s",i->second->GetName().c_str());
			}
		}
	}

	void ResourceManager::Add(const std::string& name, Resource* resource)
	{
		Assert(resource != NULL);

		if (m_Resources.find(name) != m_Resources.end())
			Logger::Log(LOGNORMAL,"%S : ressource déjà chargée !",name.c_str());

		m_Resources[name] = resource;
		resource->m_Name = name;
	}

	void ResourceManager::Remove(const std::string& name)
	{
		TResourcesMap::iterator itr = m_Resources.find(name);

		if (itr == m_Resources.end())
			Logger::Log(LOGNORMAL,"%S : ressource détruite mais non-chargée !",name.c_str());

		m_Resources.erase(itr);
	}

}
