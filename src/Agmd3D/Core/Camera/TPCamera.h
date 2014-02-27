/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef TPCAMERA_H
#define TPCAMERA_H

#include <Core\Camera\Camera.h>

namespace Agmd
{

    class AGMD3D_EXPORT TPCamera : public Camera
    {
    public:
        TPCamera(mat4& projection, vec3& pos = vec3());
        virtual ~TPCamera();

        virtual void OnUpdate(a_uint64 time_diff);

        virtual void OnMouseMotion(int x, int y);

        virtual void OnKeyboard(char key, bool up);

        virtual void OnMouseWheel(float delta);
        virtual void OnMouseWheel(bool up);

        virtual void setPosition(glm::vec3 pos);
        virtual void setTarget(glm::vec3 pos); 
    protected:
        virtual void UpdateVector();

        float _theta;
        float _phi;
        vec3 _up;
        float distance;
        bool  m_mousewheel;
    };
}

#endif //TPCAMERA_H