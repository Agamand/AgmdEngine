#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <Core/Renderer.h>
#include <Core/Camera/Camera.h>
#include <vector>



// CONSTRUCTOR / DESTRUCTOR
namespace Agmd
{
	Camera::Camera(mat4 projection, vec3 pos) :
	move(0.0f),
	moveFlags(MOVE_NONE),
	_position(pos),
	_speed(10.0f),
	_sensivity(0.2f)
	{
        //this->VectorsFromAngles();
        CameraBuffer camBuf;
        camBuf.m_MatProjection = projection;
        camBuf.m_MatView = mat4(1.0f);
        m_cameraBuffer = Renderer::Get().CreateUniformBuffer<CameraBuffer>(1,0,0,&camBuf);
    }

    void Camera::UpdateBuffer(mat4 view)
    {
        CameraBuffer* cambuf = m_cameraBuffer.Lock();
        cambuf->m_MatView = view;
        m_cameraBuffer.Unlock();
    }

	mat4 Camera::look()
	{
		return lookAt(_position,_target,vec3(0,0,1));
	}

    void Camera::SetActive()
    {
        m_cameraBuffer.Bind(UNIFORM_CAMERA_BIND);
    }

    void Camera::SetCurrent(Camera* cam)
    {
        s_currentCamera = cam;
        if(cam)
            cam->SetActive();
    }

    Camera* Camera::GetCurrent()
    {
        return s_currentCamera;
    }

    Camera* Camera::s_currentCamera = NULL;
}