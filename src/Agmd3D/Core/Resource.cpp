/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Resource.h>
#include <Core/ResourceManager.h>
//#include <Debug/New.h>


namespace Agmd
{

    Resource::Resource() :
    m_Name    (""),
    m_RefCount(1)
    {}

    Resource::~Resource()
    {
        if (m_Name != "")
            ResourceManager::Instance().Remove(m_Name);
    }

    const std::string& Resource::GetName() const
    {
        return m_Name;
    }

    void Resource::AddRef()
    {
        ++m_RefCount;
    }

    int Resource::Release()
    {
        int RefCount = --m_RefCount;

        if (RefCount == 0)
	            delete this;

        return RefCount;
    }

}
