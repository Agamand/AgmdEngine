/*
============================================================================
AgmdMaths - Maths lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

inline Transform::Transform(const vec3& _position, const quat& _rotation, const vec3& _scale) :
m_parent(NULL),
m_position(_position),
m_rotation(_rotation),
m_scale(_scale),
position(m_position),
rotation(m_rotation),
m_localMatrix(translate(mat4(1.0f),m_position)*mat4_cast(m_rotation)*glm::scale(mat4(1),m_scale)),
m_globalMatrix(m_localMatrix)
{}

inline Transform::Transform(Transform* parent, const vec3& _position, const quat& _rotation) :
m_parent(parent),
m_position(_position),
m_rotation(_rotation),
m_scale(1),
position(m_position),
rotation(m_rotation),
m_localMatrix(translate(mat4(1.0f),m_position)*mat4_cast(m_rotation)*scale(mat4(1),m_scale)),
m_globalMatrix(m_localMatrix)
{}

inline mat4 Transform::ModelMatrix() const
{
    return m_globalMatrix;//translate(mat4(1.0f),m_position)*mat4_cast(m_rotation); 
}

inline mat4 Transform::LocalModelMatrix() const
{
	return m_localMatrix;//translate(mat4(1.0f),m_position)*mat4_cast(m_rotation)*scale(mat4(1),m_scale);
}

inline void Transform::SetLocalModelMatrix(const mat4& matrix)
{
	m_localMatrix = matrix;
}

inline void Transform::Update(Transform* t)
{
	m_globalMatrix = t ? t->ModelMatrix()*m_localMatrix: m_localMatrix;
}

inline void Transform::Rotate(float angle, const vec3& vector)
{
    //m_rotation = quat(rotate(m_rotation, angle, vector));
	m_localMatrix = rotate(m_localMatrix, angle, vector);
}

inline void Transform::Translate(const vec3& move)
{
    //m_position += move;
	m_localMatrix = translate(m_localMatrix, move);
}

inline void Transform::Translate(float move_x, float move_y, float move_z)
{
    //m_position += vec3(move_x,move_y,move_z);
	m_localMatrix = translate(m_localMatrix, vec3(move_x,move_y,move_z));
}

inline void Transform::Rotate(float angle, const vec3& vector, const Transform& base)
{
    m_localMatrix = inverse(base.m_localMatrix)*rotate(mat4(1.f), angle, vector)*base.m_localMatrix*m_localMatrix;
}

inline void Transform::Rotate(quat q, const Transform& base)
{
	m_localMatrix = inverse(base.m_localMatrix)*mat4_cast(q)*base.m_localMatrix*m_localMatrix;
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