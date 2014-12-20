/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Controller/FirstPersonController.h>

namespace Agmd
{
	FirstPersonController::FirstPersonController(Transform* _transform) : m_bindedTransform(_transform),m_speed(1.f),
		_forward(0,0,1),_up(0,1,0),m_moveFlags(0)
	{
		_left = glm::cross(_up,_forward);
	}

	void FirstPersonController::onClick( int click, vec2 pos, bool up )
	{
		
	}

	void FirstPersonController::onMove( vec2 pos )
	{
		throw std::exception("The method or operation is not implemented.");
	}

	void FirstPersonController::onKey( a_char key,bool up )
	{
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
            //tempFlags = MOVE_UP;
            break;
        case 'A':
            //tempFlags = MOVE_DOWN;
            break;
        }

        if(!up)
            m_moveFlags |= tempFlags;
        else m_moveFlags &= ~tempFlags;
        updateMove();
	}
	void FirstPersonController::updateMove()
	{	
       if(m_moveFlags & MOVE_FORWARD)
           _move += _forward;

       if(m_moveFlags & MOVE_BACK)
           _move -= _forward;

       if(m_moveFlags & MOVE_LEFT)
           _move += _left;

       if(m_moveFlags & MOVE_RIGHT)
           _move -= _left;

       if(m_moveFlags & MOVE_UP)
           _move += _up;

       if(m_moveFlags & MOVE_DOWN)
		   _move -= _up;
	}
	void FirstPersonController::update( a_uint32 time )
	{
		if(!m_bindedTransform)
			return;
		m_bindedTransform->translate(_move*m_speed*(float)time,m_bindedTransform);
	}
}


