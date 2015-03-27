/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifdef _FOLLOWCAMERA_H_
#define _FOLLOWCAMERA_H_

#include <Core\Camera\Camera.h>
#include <Utilities/StringUtils.h>

namespace Agmd
{

    class AGMD3D_EXPORT FollowCamera : public Camera
    {
    public:
        FollowCamera(mat4& projection, vec3& pos = vec3());
        FollowCamera(mat4& projection, float a, float b, vec2 angle,float dist);
        virtual ~FollowCamera();

        virtual void onUpdate(a_uint64 time_diff);

        virtual void onMouseMotion(int x, int y);

        virtual void onKeyboard(a_char key, bool up);

        virtual void onMouseWheel(float delta);
        virtual void onMouseWheel(bool up);

        virtual void setPosition(glm::vec3 pos);
        virtual void setTarget(glm::vec3 pos);
        virtual const glm::vec3 getPosition();
        void SetAngles(vec2 _angles)
        {
            angles = _angles;
        }
        const vec2& GetAngles()
        {
            return angles;
        }
        mat4 look();
        const std::string toString();
    protected:
        virtual void updateVector();

        float _theta;
        float _phi;
        vec2 angles;
        vec3 _up;
        float distance;
        bool  m_mousewheel;
    };
}

#endif /* _FOLLOWCAMERA_H_ */