/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _DISPLAYABLE_H_
#define _DISPLAYABLE_H_

#include <Config/Fwd.h>
#include <Core/Resource.h>
#include <Core/Buffer/Buffer.h>
#include <Core/Declaration.h>
#include <Core/Texture/Texture.h>
#include <Core/Enums.h>
#include <Utilities/SmartPtr.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Matrix4.h>
#include <Quaternion.h>
#include <Transform.h>

using namespace AgmdMaths;

namespace Agmd
{

    class AGMD3D_EXPORT Displayable
    {
    public :
        Displayable();
        virtual ~Displayable();

        virtual void Render(TRenderPass pass) const = 0;
        virtual void Draw() const = 0;

        void Rotate(float angle, vec3 vector);
        void SetRotation(mat4 mat);
        
        void Move(vec3 move);
        void Move(float move_x, float move_y, float move_z);

        void MoveTo(vec3 pos);
        void MoveTo(float pos_x, float pos_y, float pos_z);

        vec3 getTranslate();
        mat4 getRotate();

        Transform& getPosition();


    protected:
        Transform m_transform;
        Material* m_material;
    };

}


#endif /* _DISPLAYABLE_H_ */