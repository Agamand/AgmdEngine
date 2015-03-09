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

#include <AgmdUtilities/Container/Vector.h>
namespace AgmdMaths
{
    class Transform;
    typedef Transform* TransformPtr;
    typedef a_vector<TransformPtr> TransformVector;

    class Transform
    {
    public:
        Transform(const vec3& _position = vec3(0.0f), const quat& _rotation = quat(1.0f,vec3(0.0f)),const vec3& scale = vec3(1));
        Transform(Transform* parent, const vec3& _position = vec3(0.0f), const quat& _rotation = quat(1.0f,vec3(0.0f)));
        mat4 modelMatrix() const;
		mat4 localModelMatrix() const;


		void setLocalModelMatrix(const mat4& matrix);
        void rotate(float angle, const vec3 &vector);
		void rotateRelative(float angle, const vec3 &vector);
        void translate(const vec3 &move);
		void translateRelative(const vec3 &move);
        void translate(float move_x, float move_y, float move_z);
		
		void scale(float x,float y,float z){
			m_scale.x*=x,m_scale.y*=y,m_scale.z*=z;
			m_localMatrix *=glm::scale(mat4(1),vec3(x,y,z));
			m_updateNeeded = true;
		}

		void setScale(const vec3& scale)
		{
			m_scale = scale;
		}

        void setPosition(const vec3& position);
        void SetRotation(const quat& rotation);

        //Relative transformation
        void rotate(float angle, const vec3 &vector, const Transform& base);
        void rotate(quat q, const Transform& base);
		
		void translate(const vec3 &move, const Transform& base);
        
		void translate(float move_x, float move_y, float move_z, const Transform& base);

		void update(Transform* t,bool forcedUpdate = false);
		bool needUpdate() const;

		const vec3 getPosition() const
		{
			return vec3(m_worldMatrix*vec4(0,0,0,1));
		}


		const vec3&     position;
        const quat&     rotation;

    private:
        bool            m_updateNeeded;
        vec3            m_position;
        vec3			m_scale;
		quat            m_rotation;

        mat4            m_localMatrix;
		mat4			m_worldMatrix;
        TransformPtr    m_parent;
        TransformVector m_childs;
    };

    #include <Transform.inl>
}

#endif /* _TRANSFORM_H_ */