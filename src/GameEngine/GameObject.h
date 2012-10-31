#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <Config/Fwd.h>
#include <Vector3.h>
namespace Agmd
{

	class GameObject
	{
	public:
		GameObject();
		GameObject(Model* _model);

		void setPhysicsModel();
		void setPosition(vec3 _pos)


		~GameObject();
	};
}

#endif /*GAMEOBJECT_H*/
