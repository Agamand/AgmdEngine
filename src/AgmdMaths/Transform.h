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

#include <vector>

namespace AgmdMaths
{
    class Transform;
    typedef Transform* TransformPtr;
    typedef std::vector<TransformPtr> TransformVector;

    class Transform
    {
    public:
        Transform(const vec3& _position = vec3(0.0f), const quat& _rotation = quat(1.0f,vec3(0.0f)),const vec3& scale = vec3(1));
        Transform(Transform* parent, const vec3& _position = vec3(0.0f), const quat& _rotation = quat(1.0f,vec3(0.0f)));
        mat4 ModelMatrix() const;
		mat4 LocalModelMatrix() const;


		void SetLocalModelMatrix(const mat4& matrix);
        void Rotate(float angle, const vec3 &vector);
        void Translate(const vec3 &move);
        void Translate(float move_x, float move_y, float move_z);
		
		void Scale(float x,float y,float z){
			m_scale.x*=x,m_scale.y*=y,m_scale.z*=z;
		}

		void SetScale(const vec3& scale)
		{
			m_scale = scale;
		}

        void SetPosition(const vec3& position);
        void SetRotation(const quat& rotation);

        //Relative transformation
        void Rotate(float angle, const vec3 &vector, const Transform& base);
        void Rotate(quat q, const Transform& base);
		void Translate(const vec3 &move, const Transform& base);
        
		void Translate(float move_x, float move_y, float move_z, const Transform& base);

		void Update(Transform* t);

		const vec3&     position;
        const quat&     rotation;

    private:
        bool            m_UpdateNeeded;
        vec3            m_position;
        vec3			m_scale;
		quat            m_rotation;

        mat4            m_localMatrix;
		mat4			m_globalMatrix;
        TransformPtr    m_parent;
        TransformVector m_childs;
    };

    #include <Transform.inl>
}

#endif /* _TRANSFORM_H_ */