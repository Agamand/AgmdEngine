/*
============================================================================
AgmdMaths - Maths lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <Vector3.h>
#include <Quaternion.h>
#include <Matrix4.h>

namespace AgmdMaths
{
    class Transform
    {
    public:
        Transform(vec3 _position = vec3(0.0f), quat _rotation = quat(1.0f,vec3(0.0f)));

        mat4 ModelMatrix() const;

        void Rotate(float angle, vec3 vector);
        void Translate(vec3 move);
        void Translate(float move_x, float move_y, float move_z);

        //Relative transformation
        void Rotate(float angle, vec3 vector, Transform& base);
        void Translate(vec3 move, Transform& base);
        void Translate(float move_x, float move_y, float move_z, Transform& base);

        vec3 m_position;
        quat m_rotation;
    };
    typedef Transform* TransformPtr;

#include <Transform.inl>
}

#endif /* _TRANSFORM_H_ */