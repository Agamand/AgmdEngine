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
        virtual ~Camera() {}

        virtual void OnUpdate(a_uint64 time_diff) = 0;
        virtual void OnMouseMotion(int x, int y) = 0;
        virtual void OnKeyboard(char key, bool up) = 0;
        virtual void OnMouseWheel(float delta) = 0;
        virtual void OnMouseWheel(bool up){};
        const glm::vec3& GetPosition() { return _position; }
        virtual void SetPosition(glm::vec3& pos) { _position = pos; } 
        void GetPosition(float &x, float &y, float &z) { x = _position.x; y = _position.y; z = _position.z; }
        void SetPosition(float x, float y, float z) { SetPosition(glm::vec3(x,y,z)); }

        virtual void SetTarget(glm::vec3& pos) { _target = pos; } 
        const glm::vec3& GetTarget() {return _target;}

        virtual mat4 Look();

        void SetActive(TCamera type = CAMERA_3D);

        static void SetCurrent(Camera* cam, TCamera type = CAMERA_3D);
        static Camera* GetCurrent(TCamera type = CAMERA_3D);
        bool UnProject(vec3& mousepos);
		const mat4& GetView() { return m_transform.m_MatView;} 
    protected:
        struct CameraBuffer
        {
            mat4 m_MatProjection;
            mat4 m_MatView;
        };
        virtual void UpdateVector() = 0;
        void UpdateBuffer(mat4& view);
        float _speed;
        float _sensivity;

        vec3 move;
        a_uint32 moveFlags;

        glm::vec3 _position;
        glm::vec3 _target;
        glm::vec3 _forward;
        glm::vec3 _left;
        CameraBuffer m_transform;
        float _theta;
        float _phi;
        mat4* map;

        Buffer<mat4> m_cameraBuffer;
    private:
        static Camera* s_currentCamera3D;
        static Camera* s_currentCamera2D;
    };
}
#endif