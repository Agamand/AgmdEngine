/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef FPCAMERA_H
#define FPCAMERA_H

#include <Core\Camera\Camera.h>

namespace Agmd
{

    class AGMD3D_EXPORT FPCamera : public Camera
    {
    public:
        FPCamera(mat4 projection, vec3 pos = vec3());
        virtual ~FPCamera();

        virtual void OnUpdate(uint64 time_diff);

        virtual void OnMouseMotion(int x, int y);

        virtual void OnKeyboard(char key, bool up);

        virtual void OnMouseWheel(float delta);

    protected:
        virtual void UpdateVector();

        float _theta;
        float _phi;
    };
}

#endif //FPCAMERA_H
