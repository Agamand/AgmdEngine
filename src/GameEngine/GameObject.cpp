#include <GameObject.h>
#include <vector>

namespace Agmd
{
    GameObject::GameObject(const std::string& name)
    {
		m_Name = name;
    }

    GameObject::~GameObject()
    {

    }

	const std::vector<Component*>& GameObject::GetComponents()
	{
		return m_Components;
	}	
	
	const std::vector<ObjectScript*>& GameObject::GetObjectScripts()
	{
		return m_ObjectScripts;
	}

}