#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <Core/Camera/Camera.h>
#include <vector>



// CONSTRUCTOR / DESTRUCTOR
namespace Agmd
{
	Camera::Camera(glm::vec3 pos) :
	move(0.0f),
	moveFlags(MOVE_NONE),
	_position(pos),
	_speed(10.0f),
	_sensivity(0.2f)
	{}

	mat4 Camera::look()
	{
		return lookAt(_position,_target,vec3(0,0,1));
	}


}