#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <Config/Fwd.h>
#include <GameEngineConfig/FwGameEngine.h>
#include <Vector3.h>
#include <vector>

namespace Agmd
{

    class GameObject
    {
    public:
        GameObject(const std::string& name = "GameObject");
	    ~GameObject();
		const std::vector<Component*>& GetComponents();
		const std::vector<ObjectScript*>& GetObjectScripts();
	private: 
		std::string m_Name;
		std::vector<Component*> m_Components;
		std::vector<ObjectScript*> m_ObjectScripts; 
    };
}

#endif /* _GAMEOBJECT_H_ */
