

#ifndef CAMERA_H
#define CAMERA_H

#include <Config\Export.h>
#include <Vector3.h>
#include <Matrix4.h>
#include <Utilities\Singleton.h>
#include <AgmdDefines.h>

namespace Agmd
{
	enum TCameraMove
	{
		MOVE_NONE		= 0x00,
		MOVE_FORWARD	= 0x01,
		MOVE_BACK		= 0x02,
		MOVE_LEFT		= 0x04,
		MOVE_RIGHT		= 0x08,
		MOVE_UP			= 0x10,
		MOVE_DOWN		= 0x20,
		ZOOM_IN			= 0x40,
		ZOOM_OUT        = 0x80
	};


	class AGMD_EXPORT Camera
	{
	public:
		Camera(vec3 pos);
		virtual ~Camera() {}

		virtual void OnUpdate(uint64 time_diff) = 0;
		virtual void OnMouseMotion(int x, int y) = 0;
		virtual void OnKeyboard(char key, bool up) = 0;
		virtual void OnMouseWheel(float delta) = 0;

		glm::vec3 getPosition() { return _position; }
		virtual void setPosition(glm::vec3 pos) { _position = pos; } 
		void getPosition(float &x, float &y, float &z) { x = _position.x; y = _position.y; z = _position.z; }
		void setPosition(float x, float y, float z) { setPosition(glm::vec3(x,y,z)); }

		virtual void setTarget(glm::vec3 pos) { _target = pos; } 
		glm::vec3 getTarget() {return _target;}

		virtual mat4 look();

	protected:
		virtual void VectorsFromAngles() = 0;
		float _speed;
		float _sensivity;

		vec3 move;
		uint32 moveFlags;

		glm::vec3 _position;
		glm::vec3 _target;
		glm::vec3 _forward;
		glm::vec3 _left;
		float _theta;
		float _phi;
	};
}
#endif