/*
============================================================================
AgmdMaths - Maths lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

inline Transform::Transform(const vec3& _position, const quat& _rotation) :
m_parent(NULL),
m_position(_position),
m_rotation(_rotation),
position(m_position),
rotation(m_rotation)
{}

inline Transform::Transform(Transform* parent, const vec3& _position, const quat& _rotation) :
m_parent(parent),
m_position(_position),
m_rotation(_rotation),
position(m_position),
rotation(m_rotation)
{}

inline mat4 Transform::ModelMatrix() const
{
    return translate(mat4(1.0f),m_position)*mat4_cast(m_rotation); 
}

inline void Transform::Rotate(float angle, const vec3& vector)
{
    m_rotation = quat(rotate(m_rotation, angle, vector));
}

inline void Transform::Translate(const vec3& move)
{
    m_position += move;
}

inline void Transform::Translate(float move_x, float move_y, float move_z)
{
    m_position += vec3(move_x,move_y,move_z);
}

inline void Transform::Rotate(float angle, const vec3& vector, const Transform& base)
{
    m_rotation = inverse(base.m_rotation)*quat(rotate(m_rotation, angle, vector))*base.m_rotation;
}

inline void Transform::Translate(const vec3& move, const Transform& base)
{
    //not implemented
}

inline void Transform::Translate(float move_x, float move_y, float move_z, const Transform& base)
{
    //not implemented
}

inline void Transform::SetPosition(const vec3& position)
{
    m_position = position;
}

inline void Transform::SetRotation(const quat& rotation)
{
    m_rotation = rotation;
}