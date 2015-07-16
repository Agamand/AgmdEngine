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
    Camera::Camera(TCameraProjection proj_type,ProjectionOption opt) :
//     move(0.0f),
//     moveFlags(MOVE_NONE),
//     _position(pos),
//     m_speed(100.0f),
//     m_sensivity(0.2f),
//     recvInput(true),
    m_node(NULL),
    m_frustum(new Frustum())
    {
       
        m_transform.m_MatView = mat4(1.0f);
        m_cameraBuffer = Driver::Get().CreateUniformBuffer<CameraBuffer>(1,BUF_DYNAMIC,0,1,NULL);
        setProjection(proj_type,opt);
    }

    Camera::~Camera()
    {
        m_cameraBuffer.Release();
        delete m_frustum;
    }


    void Camera::updateBuffer(mat4& inversedView)
    {
        //m_cameraBuffer.WaitSync();
        m_transform.m_MatView = inverse(inversedView);
        m_transform.m_ViewPosition = inversedView*vec4(0,0,0,1);
        m_transform.m_MatProjectionView = m_transform.m_MatProjection*m_transform.m_MatView;

		CameraBuffer buffer;
		buffer.m_MatView = transpose(m_transform.m_MatView);
		buffer.m_MatProjectionView = transpose(m_transform.m_MatProjectionView);
		buffer.m_MatProjection = transpose(m_transform.m_MatProjection);
		buffer.m_ViewPosition = m_transform.m_ViewPosition;

        //m_cameraBuffer.FillByte(&buffer,0,sizeof(CameraBuffer));
        m_cameraBuffer.Fill(&buffer,1);
		m_frustum->Setup(m_transform.m_MatProjectionView);
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
        mat4  viewprojection = inverse(m_transform.m_MatProjectionView);

        /* Map x and y from window coordinates */
        ivec2 screen = Driver::Get().GetScreen();
        mouse.x = mouse.x / screen.x;
        mouse.y = (screen.y-mouse.y) / screen.y;
        mouse.z = mouse.z*2-1;

        /* Map to range -1 to 1 */
        mouse.x = mouse.x * 2 - 1;
        mouse.y = mouse.y * 2 - 1;

        vec4 out = viewprojection*vec4(mouse,1.0f);

        if (out.w == 0.0f) return false;
        
        out.w = 1.0f / out.w;
        out*=out.w;
        mouse = vec3(out);
        //mouse /= out.x;

        //mouse -= _position;
        //mouse = normalize(mouse);

        return true;
    }

    const std::string Camera::toString()
    {
        return "Camera Object";
    }

    bool Camera::isInFrustrum( const BoundingSphere& bounding )
    {
        
        const BoundingSphere bound = bounding.GetTransformedBounding(m_transform.m_MatView);
        ShaderProgram testShader;
        //testShader.LoadFromFile("Shader/debug_shader.glsl");
        //Driver::Get().drawBoundingBox(boundingBox,testShader.GetShaderProgram());
        return m_frustum->IsIn(bound);
    }

    void Camera::updateProjection()
    {
        m_transform.m_MatProjectionView = m_transform.m_MatProjection*m_transform.m_MatView;
        //m_cameraBuffer.FillByte(&m_transform,sizeof(mat4)+sizeof(vec4),sizeof(mat4)*2);
        
//         auto a = m_cameraBuffer.Lock();
//         a->m_MatProjection = transpose(m_transform.m_MatProjection);
//         a->m_MatProjectionView = transpose(m_transform.m_MatProjectionView);
//         m_cameraBuffer.Unlock();

		CameraBuffer buffer;
		buffer.m_MatView = transpose(m_transform.m_MatView);
		buffer.m_MatProjectionView = transpose(m_transform.m_MatProjectionView);
		buffer.m_MatProjection = transpose(m_transform.m_MatProjection);
		buffer.m_ViewPosition = m_transform.m_ViewPosition;

		//m_cameraBuffer.FillByte(&buffer,0,sizeof(CameraBuffer));
        m_cameraBuffer.Fill(&buffer,1);
		m_frustum->Setup(m_transform.m_MatProjectionView);
    }

    void Camera::resize( vec2 newScreen )
    {
        if(m_projOption.flags & FLAG_IGNORE_RESIZE)
            return;
        if(m_projType == PROJECTION_PERSPECTIVE)
        {
            m_projOption.size.x = newScreen.x;
            m_projOption.size.y = newScreen.y;
            m_transform.m_MatProjection = glm::perspective(m_projOption.size.z,m_projOption.size.x/m_projOption.size.y,m_projOption.znear,m_projOption.zfar);
            updateProjection();
        }else
        {
            float p = newScreen.y/newScreen.x;
            if(m_projOption.flags & FLAG_KEEP_RESOLUTION_X)
            {
                m_projOption.size.w = m_projOption.size.y*p;
                m_projOption.size.x = m_projOption.size.z = 0.0f;//-newScreen.y*p;
            }else if(m_projOption.flags & FLAG_KEEP_RESOLUTION_X)
            {
                m_projOption.size.y = m_projOption.size.w/p;
                m_projOption.size.x = m_projOption.size.z = 0.0f;//-newScreen.y*p;
            }else
            {
                m_projOption.size.y = newScreen.x;
                m_projOption.size.w = newScreen.y;
                m_projOption.size.x = m_projOption.size.z = 0.0f;//-newScreen.y*p;
            }
            
            
            m_transform.m_MatProjection = glm::ortho(-m_projOption.size.y/2.0f,m_projOption.size.y/2.0f,-m_projOption.size.w/2.0f,m_projOption.size.w/2.0f);
            updateProjection();
        }// if ortho nothing to do
    }

	Frustum* Camera::GetFrustrum()
	{
		return m_frustum;
	}

    Camera* Camera::s_currentCamera2D = NULL;
    Camera* Camera::s_currentCamera3D = NULL;
}