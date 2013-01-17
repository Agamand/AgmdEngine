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
        GameObject(std::string = "GameObject");
	    ~GameObject();
        void setPosition(vec3 _pos);
		const std::vector<Component*>& getComponents();
		const std::vector<ObjectScript*>& getObjectScripts();
	private: 
		std::string m_name;
		std::vector<Component*> m_Components;
		std::vector<ObjectScript*> m_ObjectScripts; 
    };
}

#endif /* _GAMEOBJECT_H_ */
