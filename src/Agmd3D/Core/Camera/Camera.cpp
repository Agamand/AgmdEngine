/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <Core/Renderer.h>
#include <Core/Camera/Camera.h>
#include <vector>

namespace Agmd
{
    Camera::Camera(mat4& projection, vec3& pos) :
    move(0.0f),
    moveFlags(MOVE_NONE),
    _position(pos),
    _speed(10.0f),
    _sensivity(0.2f)
    {
        CameraBuffer camBuf;
        camBuf.m_MatProjection = projection;
        camBuf.m_MatView = mat4(1.0f);
        m_cameraBuffer = Renderer::Get().CreateUniformBuffer<CameraBuffer>(1,0,0,&camBuf);
    }

    void Camera::UpdateBuffer(mat4& view)
    {
        CameraBuffer* cambuf = m_cameraBuffer.Lock();
        cambuf->m_MatView = view;
        m_cameraBuffer.Unlock();
    }

    mat4 Camera::Look()
    {
        return lookAt(_position,_target,vec3(0,0,1));
    }

    void Camera::SetActive(TCamera type)
    {
        if(type == CAMERA_2D)
            m_cameraBuffer.Bind(UNIFORM_CAMERA2D_BIND);
        else
            m_cameraBuffer.Bind(UNIFORM_CAMERA3D_BIND);   
    }

    void Camera::SetCurrent(Camera* cam, TCamera type)
    {
        if(type == CAMERA_2D)
            s_currentCamera2D = cam;
        else
            s_currentCamera3D = cam;
        if(cam)
            cam->SetActive(type);
    }

    Camera* Camera::GetCurrent(TCamera type)
    {
        if(type == CAMERA_2D)
            return s_currentCamera2D;
        return s_currentCamera3D;
    }

    Camera* Camera::s_currentCamera2D = NULL;
    Camera* Camera::s_currentCamera3D = NULL;
}