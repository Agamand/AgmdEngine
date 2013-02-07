#include <GameObject.h>
#include <vector>

namespace Agmd
{
    GameObject::GameObject(const std::string& name) : 
    m_Name(name),
    m_mesh(NULL),
    m_rigidBody(NULL),
    m_collider(NULL),
    m_tranform(new Transform())
    {}

    GameObject::~GameObject()
    {

    }


	
	const std::vector<ObjectScript*>& GameObject::GetObjectScripts()
	{
		return m_ObjectScripts;
	}

}