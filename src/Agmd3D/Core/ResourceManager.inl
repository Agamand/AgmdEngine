/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

template <class T>
inline T* ResourceManager::Get(const std::string& name) const
{
    TResourcesMap::const_iterator itr = m_Resources.find(name);

    if (itr != m_Resources.end())
    {
        itr->second->AddRef();
        return static_cast<T*>(itr->second);
    }
    else
    {
        return NULL;
    }
}
