#ifndef TPCAMERA_H
#define TPCAMERA_H

#include <Core\Camera\Camera.h>

namespace Agmd
{

    class AGMD_EXPORT TPCamera : public Camera
    {
    public:
        TPCamera(mat4 projection, vec3 pos = vec3());
        virtual ~TPCamera();

        virtual void OnUpdate(uint64 time_diff);

        virtual void OnMouseMotion(int x, int y);

        virtual void OnKeyboard(char key, bool up);

        virtual void OnMouseWheel(float delta);

        virtual void setPosition(glm::vec3 pos);
        virtual void setTarget(glm::vec3 pos); 
    protected:
        virtual void VectorsFromAngles();

        float _theta;
        float _phi;
        float distance;
    };
}

#endif //TPCAMERA_H