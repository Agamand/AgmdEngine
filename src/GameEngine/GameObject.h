#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <Config/Fwd.h>
#include <GameEngineConfig/FwGameEngine.h>
#include <GameEngineConfig/ExportGameEngine.h>
#include <Core/RenderObject/Displayable.h>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <Vector3.h>
#include <vector>

namespace Agmd
{

    class GAMEENGINE_EXPORT GameObject
    {
    public:
        GameObject(const std::string& name = "GameObject");
	    ~GameObject();
		const std::vector<ObjectScript*>& GetObjectScripts();
        

        template <class T> void AddComponent();
        template <class T> const T* GetComponent();
	private: 
		std::string m_Name;
		std::vector<ObjectScript*> m_ObjectScripts;

        /* 3D ENGINE VAR BEGIN */

        Displayable* m_mesh;
        Transform* m_tranform;

        /*3D ENGINE VAR END*/

        /* Bullet VAR BEGIN */

        btRigidBody* m_rigidBody;
        btCollisionShape* m_collider;

        /* Bullet VAR END*/
    };

    #include "GameObject.inl"

    template <class T> void GameObject::AddComponent()
    {}

    template <class T> const T* GameObject::GetComponent()
    {}

    /*template <Displayable> const T* GameObject::GetComponent()
    {}*/
    /*
    template <Transform> const T* GameObject::GetComponent()
    {}
    
    template <btRigidBody> void GameObject::AddComponent()
    {
        //delete m_rigidBody;
        //m_rigidBody = new btRigidBody();
    }
    template <btRigidBody> const T* GameObject::GetComponent()
    {}

    template <btCollisionShape> void GameObject::AddComponent()
    {}
    template <btCollisionShape> const T* GameObject::GetComponent()
    {}*/
}

#endif /* _GAMEOBJECT_H_ */
