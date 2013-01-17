#include <GameObject.h>
#include <vector>

namespace Agmd
{
    GameObject::GameObject(std::string name)
    {
		m_name = std::string(name);
    }

    GameObject::~GameObject()
    {

    }

	const std::vector<Component*>& GameObject::getComponents()
	{
		return m_Components;
	}	
	
	const std::vector<ObjectScript*>& GameObject::getObjectScripts()
	{
		return m_ObjectScripts;
	}

}