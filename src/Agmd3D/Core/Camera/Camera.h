/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef CAMERA_H
#define CAMERA_H

#include <Config/Export.h>
#include <Core/Buffer/Buffer.h>
#include <Core/Enums.h>
#include <Vector3.h>
#include <Matrix4.h>
#include <Core/Tools/Frustum.h>
#include <CommonDefines.h>

namespace Agmd
{
//     enum TCameraMove
//     {
//         MOVE_NONE        = 0x00,
//         MOVE_FORWARD    = 0x01,
//         MOVE_BACK        = 0x02,
//         MOVE_LEFT        = 0x04,
//         MOVE_RIGHT        = 0x08,
//         MOVE_UP            = 0x10,
//         MOVE_DOWN        = 0x20,
//         ZOOM_IN            = 0x40,
//         ZOOM_OUT        = 0x80
//     };


	enum TCameraProjection
	{
		PROJECTION_PERSPECTIVE,
		PROJECTION_ORTHO
	};

	enum TCameraFlags
	{
		FLAG_KEEP_RESOLUTION_X = 0x1,
		FLAG_KEEP_RESOLUTION_Y = 0x2,
		FLAG_CENTER = 0x4,
		FLAG_IGNORE_RESIZE = 0x8
	};
	struct ProjectionOption
	{
		ProjectionOption(vec2 _size=vec2(),a_uint8 _flags = 0):
			size(-_size.x,_size.x,-_size.y,_size.y),
			znear(0.01f),
			zfar(1000.f),
			flags(_flags)
		{}
		ProjectionOption(vec2 _size,float fov,a_uint8 _flags = 0):
			size(_size.x,_size.y,fov,0),
			znear(0.01f),
			zfar(1000.f),
			flags(_flags)
		{}
		ProjectionOption(vec4 _size,a_uint8 _flags=0):
			size(_size),
			znear(0.01f),
			zfar(1000.f),
			flags(_flags)
		{}
		vec4 size;
		float znear;
		float zfar;
		a_uint8 flags;
		

	};



    class AGMD3D_EXPORT Camera
    {
	friend class CameraNode;
    public:
        //Camera(mat4& projection);
		Camera(TCameraProjection proj_type,ProjectionOption);

		void setProjection(TCameraProjection proj_type,const ProjectionOption& opt)
		{
			m_projOption = opt;
			m_projType = proj_type;
			if(m_projType == PROJECTION_PERSPECTIVE)
				m_transform.m_MatProjection = m_transform.m_MatProjection = glm::perspective(m_projOption.size.z,m_projOption.size.x/m_projOption.size.y,m_projOption.znear,m_projOption.zfar);
			else m_transform.m_MatProjection = m_transform.m_MatProjection = glm::ortho(m_projOption.size.x,m_projOption.size.y,m_projOption.size.z,m_projOption.size.w,m_projOption.znear,m_projOption.zfar);
			updateProjection();
		}
		const ProjectionOption& getProjectionOption() const { return m_projOption;}
		const TCameraProjection getProjectionType() const {return m_projType;}

		void resize(vec2 newScreen);
        virtual ~Camera();

//         virtual void onUpdate(a_uint64 time_diff) = 0;
//         virtual void onMouseMotion(int x, int y) = 0;
// 		virtual void onKeyboard(a_char key, bool up) = 0;
//         virtual void onMouseWheel(float delta) = 0;
//         virtual void onMouseWheel(bool up){};
//         virtual const glm::vec3 getPosition() { return _position; }
//         virtual void SetPosition(glm::vec3& pos) { _position = pos; } 
//         void getPosition(float &x, float &y, float &z) { x = _position.x; y = _position.y; z = _position.z; }
/*        void SetPosition(float x, float y, float z) { SetPosition(glm::vec3(x,y,z)); }*/

        //virtual void setTarget(glm::vec3& pos) { _target = pos; } 
        //const glm::vec3& getTarget() {return _target;}

        virtual mat4 look();

        void setActive(TCamera type = CAMERA_3D);
        static void setCurrent(Camera* cam, TCamera type = CAMERA_3D);
        static Camera* getCurrent(TCamera type = CAMERA_3D);
        bool unProject(vec3& mousepos);
		const mat4& getView() { return m_transform.m_MatView; } 
		const mat4& getProjection() { return m_transform.m_MatProjection; }
		virtual const std::string toString();
		bool isInFrustrum(const BoundingBox& boundingBox);
		//void SetRecvInput(bool active = true){	recvInput = active;	}
		//float* GetSpeedPtr(){return &m_speed;}
		SceneNode* getNode() { return m_node;}
    protected:
        
        //virtual void updateVector() = 0;
        void updateBuffer(mat4& view);
		void updateProjection();
		struct CameraBuffer
		{
			mat4 m_MatProjectionView;
			mat4 m_MatView;
			mat4 m_MatProjection;
		};

//         float m_speed;
//         float m_sensivity;
// 
//         vec3 move;
//         a_uint32 moveFlags;
// 
//         glm::vec3 _position;
//         glm::vec3 _target;
//         glm::vec3 _forward;
//         glm::vec3 _left;
        CameraBuffer m_transform;
//         float _theta;
//         float _phi;
// 		bool				recvInput;
		Frustum*			m_frustum;
        Buffer<CameraBuffer> m_cameraBuffer;
		SceneNode*			m_node;
    private:
        static Camera* s_currentCamera3D;
        static Camera* s_currentCamera2D;
		ProjectionOption m_projOption;
		TCameraProjection m_projType;
	};
}
#endif