/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifdef FPCAMERA_H
#define FPCAMERA_H

#include <Core\Camera\Camera.h>

namespace Agmd
{

    class AGMD3D_EXPORT FPCamera : public Camera
    {
    public:
        FPCamera(mat4& projection, vec3& pos = vec3());
        virtual ~FPCamera();

        virtual void onUpdate(a_uint64 time_diff);

        virtual void onMouseMotion(int x, int y);

		virtual void onKeyboard(a_char key, bool up);

        virtual void onMouseWheel(float delta);

    protected:
        virtual void updateVector();

		virtual mat4 look();


        float _theta;
		float _phi;
		quat m_rotation;
		mat4 m_view;
    };
}

#endif //FPCAMERA_H
