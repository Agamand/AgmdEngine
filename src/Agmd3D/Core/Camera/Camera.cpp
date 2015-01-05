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

#include <Core/Driver.h>
#include <Core/Camera/Camera.h>
#include <Core/Tools/BoundingBox.h>
#include <Core/Shader/ShaderProgram.h>

#include <Container/Vector.h>

#include <Debug/Profiler.h>


namespace Agmd
{
    Camera::Camera(mat4& projection) :
//     move(0.0f),
//     moveFlags(MOVE_NONE),
//     _position(pos),
//     m_speed(100.0f),
//     m_sensivity(0.2f),
// 	recvInput(true),
	m_node(NULL),
	m_frustum(new Frustum(projection))
    {
        m_transform.m_MatProjection = projection;
        m_transform.m_MatView = mat4(1.0f);
        m_cameraBuffer = Driver::Get().CreateUniformBuffer<CameraBuffer>(1,BUF_DYNAMIC,0,1,NULL);
        m_transform.m_MatProjectionView = m_transform.m_MatProjection*m_transform.m_MatView;
        m_cameraBuffer.Fill(&m_transform,1);
    }

	Camera::~Camera()
	{
		m_cameraBuffer.Release();
		delete m_frustum;
	}


    void Camera::updateBuffer(mat4& view)
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

    mat4 Camera::look()
    {
        return mat4();//lookAt(_position,_target,vec3(0,1,0));
    }

    void Camera::setActive(TCamera type)
    {
        if(type == CAMERA_2D)
            m_cameraBuffer.Bind(UNIFORM_CAMERA2D_BIND);
        else
            m_cameraBuffer.Bind(UNIFORM_CAMERA3D_BIND);   
    }

    void Camera::setCurrent(Camera* cam, TCamera type)
    {
        if(type == CAMERA_2D)
            s_currentCamera2D = cam;
        else
            s_currentCamera3D = cam;
        if(cam)
            cam->setActive(type);
    }

    Camera* Camera::getCurrent(TCamera type)
    {
        if(type == CAMERA_2D)
            return s_currentCamera2D;
        return s_currentCamera3D;
    }

    bool Camera::unProject(vec3& mouse)
    {
        mat4 viewprojection = m_transform.m_MatProjection*m_transform.m_MatView;
        viewprojection = inverse(viewprojection);

        /* Map x and y from window coordinates */
        ivec2 screen = Driver::Get().GetScreen();
        mouse.x = mouse.x / screen.x;
        mouse.y = mouse.y / screen.y;

        /* Map to range -1 to 1 */
        mouse.x = mouse.x * 2 - 1;
        mouse.y = mouse.y * 2 - 1;

        vec4 out = viewprojection*vec4(mouse,1.0f);

        if (out.w == 0.0) return false;
   
        mouse = vec3(out);
        mouse /= out.x;

        //mouse -= _position;
        mouse = normalize(mouse);

        return true;
    }

	const std::string Camera::toString()
	{
		return "Camera Object";
	}

	bool Camera::isInFrustrum( const BoundingBox& boundingBox )
	{
		return true;
		const BoundingBox bbox = boundingBox.getTransformedBoundingBox(m_transform.m_MatView);
		ShaderProgram testShader;
		testShader.LoadFromFile("Shader/debug_shader.glsl");
		Driver::Get().drawBoundingBox(boundingBox,testShader.GetShaderProgram());
		return m_frustum->IsIn(bbox);
	}

	Camera* Camera::s_currentCamera2D = NULL;
    Camera* Camera::s_currentCamera3D = NULL;
}