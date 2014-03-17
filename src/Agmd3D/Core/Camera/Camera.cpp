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
#include <Debug/Profiler.h>

namespace Agmd
{
    Camera::Camera(mat4& projection, vec3& pos) :
    move(0.0f),
    moveFlags(MOVE_NONE),
    _position(pos),
    _speed(100.0f),
    _sensivity(0.2f),
    map(NULL)
    {
        m_transform.m_MatProjection = projection;
        m_transform.m_MatView = mat4(1.0f);
        m_cameraBuffer = Renderer::Get().CreateUniformBuffer<CameraBuffer>(1,BUF_DYNAMIC,0,1,NULL);
        //m_cameraBuffer.SwapBuffers();
        m_transform.m_MatProjectionView = m_transform.m_MatProjection*m_transform.m_MatView;
        m_cameraBuffer.Fill(&m_transform,1);
    }

    void Camera::UpdateBuffer(mat4& view)
    {
        //m_cameraBuffer.WaitSync();
        m_transform.m_MatView = view;
        m_transform.m_MatProjectionView = m_transform.m_MatProjection*m_transform.m_MatView;
        m_cameraBuffer.FillByte(&m_transform,0,sizeof(mat4)*2);
        /*if(map == NULL)
            map = m_cameraBuffer.LockBits<mat4>(0, sizeof(mat4),LOCK_WRITEONLY | LOCK_UNSYNCHRONOUS);
        mat4 vp = m_transform.m_MatProjection*m_transform.m_MatView;
        *map = m_transform.m_MatProjection*m_transform.m_MatView;
        m_cameraBuffer.SwapBuffers();
        map = NULL;*/
        
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

    bool Camera::UnProject(vec3& mouse)
    {
        mat4 viewprojection = m_transform.m_MatProjection*m_transform.m_MatView;
        viewprojection = inverse(viewprojection);

        /* Map x and y from window coordinates */
        ivec2 screen = Renderer::Get().GetScreen();
        mouse.x = mouse.x / screen.x;
        mouse.y = mouse.y / screen.y;

        /* Map to range -1 to 1 */
        mouse.x = mouse.x * 2 - 1;
        mouse.y = mouse.y * 2 - 1;

        vec4 out = viewprojection*vec4(mouse,1.0f);

        if (out.w == 0.0) return false;
   
        mouse = vec3(out);
        mouse /= out.x;

        mouse -= _position;
        mouse = normalize(mouse);

        return true;
    }

	const std::string Camera::ToString()
	{
		return "Camera(Abstract)";
	}

	Camera* Camera::s_currentCamera2D = NULL;
    Camera* Camera::s_currentCamera3D = NULL;
}