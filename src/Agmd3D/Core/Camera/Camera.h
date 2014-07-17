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
    enum TCameraMove
    {
        MOVE_NONE        = 0x00,
        MOVE_FORWARD    = 0x01,
        MOVE_BACK        = 0x02,
        MOVE_LEFT        = 0x04,
        MOVE_RIGHT        = 0x08,
        MOVE_UP            = 0x10,
        MOVE_DOWN        = 0x20,
        ZOOM_IN            = 0x40,
        ZOOM_OUT        = 0x80
    };


    class AGMD3D_EXPORT Camera
    {
    public:
        Camera(mat4& projection, vec3& pos);
        virtual ~Camera();

        virtual void onUpdate(a_uint64 time_diff) = 0;
        virtual void onMouseMotion(int x, int y) = 0;
        virtual void onKeyboard(char key, bool up) = 0;
        virtual void onMouseWheel(float delta) = 0;
        virtual void onMouseWheel(bool up){};
        virtual const glm::vec3 getPosition() { return _position; }
        virtual void SetPosition(glm::vec3& pos) { _position = pos; } 
        void getPosition(float &x, float &y, float &z) { x = _position.x; y = _position.y; z = _position.z; }
        void SetPosition(float x, float y, float z) { SetPosition(glm::vec3(x,y,z)); }

        virtual void setTarget(glm::vec3& pos) { _target = pos; } 
        const glm::vec3& getTarget() {return _target;}

        virtual mat4 look();

        void setActive(TCamera type = CAMERA_3D);
        static void setCurrent(Camera* cam, TCamera type = CAMERA_3D);
        static Camera* getCurrent(TCamera type = CAMERA_3D);
        bool unProject(vec3& mousepos);
		const mat4& getView() { return m_transform.m_MatView; } 
		const mat4& getProjection() { return m_transform.m_MatProjection; }
		virtual const std::string toString();
		bool isInFrustrum(const BoundingBox& boundingBox);
		void SetRecvInput(bool active = true){	recvInput = active;	}
		float* GetSpeedPtr(){return &m_speed;}
    protected:
        
        virtual void updateVector() = 0;
        void updateBuffer(mat4& view);

		struct CameraBuffer
		{
			mat4 m_MatProjectionView;
			mat4 m_MatView;
			mat4 m_MatProjection;
		};

        float m_speed;
        float m_sensivity;

        vec3 move;
        a_uint32 moveFlags;

        glm::vec3 _position;
        glm::vec3 _target;
        glm::vec3 _forward;
        glm::vec3 _left;
        CameraBuffer m_transform;
        float _theta;
        float _phi;
		bool				recvInput;
		Frustum*			m_frustum;
        Buffer<CameraBuffer> m_cameraBuffer;
		
    private:
        static Camera* s_currentCamera3D;
        static Camera* s_currentCamera2D;
    };
}
#endif