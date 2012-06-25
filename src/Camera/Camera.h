

#ifndef CAMERA_H
#define CAMERA_H

#include <Maths\Vector3.h>
#include <Maths\Matrix4.h>
#include <Utilities\Singleton.h>
#include <AgmdDefines.h>

namespace Agmd
{
	class AGMD_EXPORT Camera : public CSingleton<Camera>
	{

		MAKE_SINGLETON(Camera)
	public:
		Camera(vec3 pos = vec3());
		~Camera();

		virtual void OnMouseMotion(int x, int y);
		virtual void OnKeyboard(char key);

		virtual void VectorsFromAngles();

		glm::vec3 getPosition() { return _position; }
		void setPosition(glm::vec3 pos) { _position = pos; } 
		void getPosition(float &x, float &y, float &z) { x = _position.x; y = _position.y; z = _position.z; }
		void setPosition(float x, float y, float z) { _position = glm::vec3(x,y,z); }

		void setTarget(glm::vec3 pos) { _target = pos; } 
		glm::vec3 getTarget() {return _target;}

		mat4 look();

	private:
		float _speed;
		float _sensivity;

		int32 _timeBeforeStoppingVerticalMotion;
		int _verticalMotionActive;
		int _verticalMotionDirection;

		glm::vec3 _position;
		glm::vec3 _target;
		glm::vec3 _forward;
		glm::vec3 _left;
		float _theta;
		float _phi;
	};
}
#endif