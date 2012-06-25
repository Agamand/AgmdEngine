#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <Camera/Camera.h>
#include <vector>



// CONSTRUCTOR / DECONSTRUCTOR
namespace Agmd
{
	SINGLETON_IMPL(Camera)
	Camera::Camera(glm::vec3 pos)
	{
		_position = pos;
		_phi = 0;
		_theta = 0;
		VectorsFromAngles();

		_speed = 0.1f;
		_sensivity = 0.2;
		_verticalMotionActive = 0;
	}

	// FUNCTION

	void Camera::VectorsFromAngles()
	{
		glm::vec3 up(0.0f,0.0f,1.0f);
		float r_temp = cos(_phi*M_PI/180);
		if (_phi > 89)
			_phi = 89;
		else if (_phi < -89)
			_phi = -89;
    
		_forward = glm::vec3(r_temp*cos(_theta*M_PI/180),r_temp*sin(_theta*M_PI/180),sin(_phi*M_PI/180));
		_left = glm::cross(up,_forward);
		glm::normalize(_left);

	   _target = _position + _forward;
	}
	void Camera::OnMouseMotion(int x, int y)
	{
		_theta -= x*_sensivity;
		_phi += y*_sensivity;
		VectorsFromAngles();
	}

	void Camera::OnKeyboard(char key)
	{
		glm::vec3 up(0.0f,0.0f,1.0f);
		switch(key)
		{
		case 'z':
			_position = _position + _forward * _speed;
			break;
		case 's':
			_position = _position - _forward * _speed;
			break;
		case 'q':
			_position = _position + _left * _speed;
			break;
		case 'd':
			_position = _position - _left * _speed;
			break;
		case 'e':
			_position = _position + up * _speed;
			break;
		case 'a':
			_position = _position - up * _speed;
			break;
		}

		VectorsFromAngles();

		_target = _position + _forward;
	}

	mat4 Camera::look()
	{
		return lookAt(_position,_target,vec3(0,0,1));
	}
}