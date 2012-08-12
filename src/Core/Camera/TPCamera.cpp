#include <Core\Camera\TPCamera.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace Agmd
{
	TPCamera::TPCamera(vec3 pos) :
	Camera(pos),
	_phi(0),
	_theta(0),
	distance(30.0f)
	{}

	TPCamera::~TPCamera()
	{}

	void TPCamera::VectorsFromAngles()
	{
		glm::vec3 up(0.0f,0.0f,1.0f);
		float r_temp = cos(_phi*((float)M_PI)/180);
		if (_phi > 89)
			_phi = 89;
		else if (_phi < -89)
			_phi = -89;
    
		_forward = glm::vec3(r_temp*cos(_theta*M_PI/180),r_temp*sin(_theta*M_PI/180),sin(_phi*M_PI/180));
		_left = glm::cross(up,_forward);
		glm::normalize(_left);

	  _position  =  _target - distance*_forward;
	   move = vec3(0.0f);

	   if(moveFlags & MOVE_FORWARD)
		   move += _forward;

	   if(moveFlags & MOVE_BACK)
		   move -= _forward;

	   if(moveFlags & MOVE_LEFT)
		   move += _left;

	   if(moveFlags & MOVE_RIGHT)
		   move -= _left;

	   if(moveFlags & MOVE_UP)
		   move += vec3(0.0f,0.0f,1.0f);

	   if(moveFlags & MOVE_DOWN)
		   move -= vec3(0.0f,0.0f,1.0f);

	}
	void TPCamera::OnMouseMotion(int x, int y)
	{
		_theta += x*_sensivity;
		_phi += y*_sensivity;
		VectorsFromAngles();
	}

	void TPCamera::OnKeyboard(char key, bool up)
	{
		uint32 tempFlags = MOVE_NONE;
		switch(key)
		{
		case 'Z':
			tempFlags = MOVE_FORWARD;
			break;
		case 'S':
			tempFlags = MOVE_BACK;
			break;
		case 'Q':
			tempFlags = MOVE_LEFT;
			break;
		case 'D':
			tempFlags = MOVE_RIGHT;
			break;
		case 'E':
			tempFlags = MOVE_UP;
			break;
		case 'A':
			tempFlags = MOVE_DOWN;
			break;
		case 33:
			tempFlags = ZOOM_IN;
			break;
		case 34:
			tempFlags = ZOOM_OUT;
			break;
		}

		if(!up)
			moveFlags |= tempFlags;
		else moveFlags &= ~tempFlags;
		VectorsFromAngles();
	}

	void TPCamera::OnUpdate(uint64 time_diff)
	{
		if(moveFlags & ZOOM_IN)
			distance -= _speed*time_diff/1000.0f;
		else if( moveFlags & ZOOM_OUT)
			distance += _speed*time_diff/1000.0f;

		if(distance < 1.0f)
			distance = 1.0f;

		_target += move*(_speed*time_diff)/1000.0f;
		_position = _target - distance*_forward;
	}
}