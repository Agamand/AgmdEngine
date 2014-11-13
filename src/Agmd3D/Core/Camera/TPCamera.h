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

        virtual void onUpdate(a_uint64 time_diff);

        virtual void onMouseMotion(int x, int y);

		virtual void onKeyboard(a_char key, bool up);

        virtual void onMouseWheel(float delta);
        virtual void onMouseWheel(bool up);

        virtual void setPosition(glm::vec3 pos);
        virtual void setTarget(glm::vec3 pos); 
    protected:
        virtual void updateVector();

        float _theta;
        float _phi;
        vec3 _up;
        float distance;
        bool  m_mousewheel;
    };
}

#endif //TPCAMERA_H