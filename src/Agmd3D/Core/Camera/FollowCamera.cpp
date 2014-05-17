/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core\Camera\FollowCamera.h>
#define _USE_MATH_DEFINES
#include <math.h>


namespace Agmd
{
    FollowCamera::FollowCamera(mat4& projection, vec3& pos) :
    _up(0,0,1),
    distance(30.0f),
    m_mousewheel(false),
    Camera(projection,pos)
    {
        //UpdateVector();
		_forward = vec3(1,0,0);
		_left = vec3(0,-1,0);
		_phi = 0;
		_theta = 0;
    }

	FollowCamera::FollowCamera( mat4& projection, float a, float b, vec2 angle,float dist ) :
		_up(0,0,1),
		distance(dist),
		m_mousewheel(false),
		angles(angle),
		Camera(projection,vec3())
	{
		//UpdateVector();
		_forward = vec3(1,0,0);
		_left = vec3(0,-1,0);
		_phi = b;
		_theta = a;
	}

    FollowCamera::~FollowCamera()
    {}

    void FollowCamera::UpdateVector()
    {
		move = vec3(0);
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
    void FollowCamera::OnMouseMotion(int x, int y)
    {
		if(!recvInput)
			return;
        if(m_mousewheel)
        {
            _target += -_left*(float)x*0.1f;
            _target += _up*(float)y*0.1f;
        }
        else
        {
            _theta += x*_sensivity;
            _phi += y*_sensivity;
        
        }
        UpdateVector();
    }

    void FollowCamera::OnKeyboard(char key, bool up)
    {
		if(!recvInput)
			return;
        a_uint32 tempFlags = MOVE_NONE;
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
        UpdateVector();
    }

    void FollowCamera::OnUpdate(a_uint64 time_diff)
    {
        if(moveFlags & ZOOM_IN)
            distance -= _speed*0.1f*time_diff/1000.0f;
        else if( moveFlags & ZOOM_OUT)
            distance += _speed*0.1f*time_diff/1000.0f;

        if(distance < 1.0f)
            distance = 1.0f;
		angles += vec2(move*(_speed*time_diff)/(float)pow(2,4/distance)/1000.0f);
        _target += move*(_speed*time_diff)/1000.0f;
        _position = _target - distance*_forward;
        UpdateBuffer(Look());
    }

    
    void FollowCamera::setPosition(glm::vec3 pos)
    {
        _forward = _target - pos;
        _forward =  normalize(_forward);

        _phi = asinf(_forward.z);
        float costheta = _forward.x/_phi;
        float sintheta = _forward.y/_phi;
        if(costheta != 0.0f)
        {
            _theta = atan(sintheta/costheta);
        }else if( sintheta > 0)
        {
            _theta = 90;
        }else _theta = -90;

        _phi *= 180/(float)M_PI;
        

        UpdateVector();

    }

	mat4 FollowCamera::Look()
	{
		return lookAt(vec3(0,0,0),vec3(1,0,0),vec3(0,0,1))*rotate(mat4(1),_phi,vec3(0,1,0))*rotate(mat4(1),_theta,vec3(1,0,0))*translate(mat4(1.f),vec3(distance,0,0))*rotate(mat4(1),angles.x,vec3(0,1,0))*rotate(mat4(1),angles.y,vec3(0,0,1));
	}

    void FollowCamera::OnMouseWheel(float delta)
    {
		if(!recvInput)
			return;
		float f = pow(2,4/distance);
		printf("factor %f",f);
        distance += delta/f*0.001f;
		if(distance < 0.90f)
			distance = 0.90f;
        UpdateVector();
    }
    void FollowCamera::OnMouseWheel(bool up)
    {
		if(!recvInput)
			return;
        m_mousewheel = up;
    }

    void FollowCamera::setTarget(glm::vec3 pos)
    {
        Camera::SetTarget(pos);
        _position = _target - distance*_forward;
    }

	const std::string FollowCamera::ToString()
	{
		return StringBuilder("Follow Camera Theta(")(_theta)(") _phi(")(_phi)(") angles(")(angles.x)(",")(angles.y)(") distance(")(distance)(")\n");
	}

	const vec3 FollowCamera::GetPosition()
	{
		return vec3(inverse(Look())*vec4(0,0,0,1));
	}

}