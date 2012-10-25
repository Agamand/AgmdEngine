#include <Core\Camera\DynamicCamera.h>
#include <Core\Model.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace Agmd
{
	DynamicCamera::DynamicCamera(vec3 pos) :
	m_transfo(NULL),
	Camera(pos)
	{
		VectorsFromAngles();
	}

	DynamicCamera::~DynamicCamera()
	{
	}

	void DynamicCamera::VectorsFromAngles()
	{
		/*glm::vec3 up(0.0f,0.0f,1.0f);
		float r_temp = cos(_phi*((float)M_PI)/180);
		if (_phi > 89)
			_phi = 89;
		else if (_phi < -89)
			_phi = -89;
    
		_forward = glm::vec3(r_temp*cos(_theta*M_PI/180),r_temp*sin(_theta*M_PI/180),sin(_phi*M_PI/180));
		_left = glm::cross(up,_forward);
		glm::normalize(_left);

	   _target = _position + _forward;
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
		   move -= vec3(0.0f,0.0f,1.0f);*/
	}
	void DynamicCamera::OnMouseMotion(int /*x*/, int /*y*/)
	{}

	void DynamicCamera::OnKeyboard(char /*key*/, bool /*up*/)
	{}

	void DynamicCamera::OnMouseWheel(float /*delta*/)
	{}
	
	mat4 DynamicCamera::look()
	{
		mat4 view = lookAt(vec3(0),vec3(1.0f,0,0),vec3(0,0,1));
		if(m_transfo != NULL)
			view = view*inverse(m_transfo->ModelMatrix());
		return view;
	}

	void DynamicCamera::OnUpdate(uint64 /*time_diff*/)
	{}


	void DynamicCamera::setLinkTransfo(ModelTransfo* _transfo)
	{
		m_transfo = _transfo;
	}
}