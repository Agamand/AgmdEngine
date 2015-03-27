/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Controller/FirstPersonController.h>
#include <Core/SceneNode/SceneNode.h>
namespace Agmd
{
    FirstPersonController::FirstPersonController() : InputController(),m_speed(0.02f),
        _forward(0,0,1),_up(0,1,0),m_moveFlags(0),m_mouseState(0),m_angularSpeed(0.08f)
    {
        _left = glm::cross(_up,_forward);
        m_sensivity = 0.2f;
    }

    void FirstPersonController::OnClick( int click,int state, const vec2& pos, bool up )
    {
        m_mouseState = state;
    }

    void FirstPersonController::OnMouseMotion( const vec2& pos, const ivec2& posDiff)
    {
        
        if(m_bindedNode)
        {
            if(m_mouseState & MOUSE_RIGHT)
            {
                m_bindedNode->getTransform().rotateRelative(posDiff.x*m_sensivity,vec3(0,1,0));
                m_bindedNode->getTransform().rotateRelative(posDiff.y*m_sensivity,vec3(1,0,0));
            }
        }
    }

    void FirstPersonController::OnKey( char key, bool up )
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
            tempFlags = ROLL_RIGHT;
            break;
        case 'A':
            tempFlags = ROLL_LEFT;
            break;
        }

        if(!up)
            m_moveFlags |= tempFlags;
        else m_moveFlags &= ~tempFlags;
        updateMove();
    }
    void FirstPersonController::updateMove()
    {    
       _move = vec3(0);
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
        if(!m_bindedNode)
            return;
        Transform& t = m_bindedNode->getTransform();
        t.translateRelative(-_move*m_speed*(float)time);
        if(m_moveFlags & ROLL_LEFT  ^ m_moveFlags & ROLL_RIGHT) // XOR 
        {
            if(m_moveFlags & ROLL_LEFT)
                m_bindedNode->getTransform().rotateRelative(m_angularSpeed*(float)time,vec3(0,0,1));
            else
                m_bindedNode->getTransform().rotateRelative(-m_angularSpeed*(float)time,vec3(0,0,1));
            
        }
    }
}


