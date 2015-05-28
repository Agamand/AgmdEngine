/*
============================================================================
AgmdMaths - Maths lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

inline Transform::Transform(const vec3& _position, const quat& _rotation, const vec3& _scale) :
m_updateNeeded(false),
m_parent(NULL),
m_position(_position),
m_rotation(_rotation),
m_scale(_scale),
position(m_position),
rotation(m_rotation),
m_localMatrix(glm::translate(mat4(1.0f),m_position)*mat4_cast(m_rotation)*glm::scale(mat4(1),m_scale)),
m_worldMatrix(m_localMatrix)
{}

inline Transform::Transform(Transform* parent, const vec3& _position, const quat& _rotation) :
m_updateNeeded(false),
m_parent(parent),
m_position(_position),
m_rotation(_rotation),
m_scale(1),
position(m_position),
rotation(m_rotation),
m_localMatrix(glm::translate(mat4(1.0f),m_position)*glm::mat4_cast(m_rotation)*glm::scale(mat4(1),m_scale)),
m_worldMatrix(m_localMatrix)

{}

inline mat4 Transform::modelMatrix() const
{
    return m_worldMatrix;//translate(mat4(1.0f),m_position)*mat4_cast(m_rotation); 
}

inline mat4 Transform::localModelMatrix() const
{
    return m_localMatrix;//translate(mat4(1.0f),m_position)*mat4_cast(m_rotation)*scale(mat4(1),m_scale);
}

inline void Transform::setLocalModelMatrix(const mat4& matrix)
{
    m_localMatrix = matrix*glm::scale(mat4(1),m_scale); 
    m_updateNeeded=true;
}

inline void Transform::update(Transform* t,bool forcedUpdate)
{
    m_worldMatrix = t ? t->modelMatrix()*m_localMatrix: m_localMatrix;
    m_updateNeeded=false;
}

inline void Transform::rotate(float angle, const vec3& vector)
{
    m_rotation = glm::rotate(quat(), angle, vector)*m_rotation;
    m_localMatrix = glm::translate(mat4(1),m_position)*mat4_cast(m_rotation)*glm::scale(mat4(1),m_scale);
    m_updateNeeded=true;
}

inline void Transform::translate(const vec3& move)
{
    m_position +=move;
    m_localMatrix = glm::translate(mat4(1),m_position)*mat4_cast(m_rotation)*glm::scale(mat4(1),m_scale);
    m_updateNeeded=true;
}

inline void Transform::translate(float move_x, float move_y, float move_z)
{
    translate(vec3(move_x,move_y,move_z));
}

inline void Transform::rotate(float angle, const vec3& vector, const Transform& base)
{
    //m_localMatrix = glm::inverse(base.m_localMatrix)*glm::rotate(mat4(1.f), angle, vector)*base.m_localMatrix*m_localMatrix;
    m_updateNeeded=true;
}

inline void Transform::rotate(quat q, const Transform& base)
{
    //m_localMatrix = glm::inverse(base.m_localMatrix)*glm::mat4_cast(q)*base.m_localMatrix*m_localMatrix;
    m_updateNeeded=true;
}

inline void Transform::translate(const vec3& move, const Transform& base)
{
    //not implemented
}

inline void Transform::translate(float move_x, float move_y, float move_z, const Transform& base)
{
    //not implemented
}

inline void Transform::setPosition(const vec3& position)
{
    m_position = position;
    m_localMatrix = glm::translate(mat4(1),m_position)*mat4_cast(m_rotation)*glm::scale(mat4(1),m_scale);
    m_updateNeeded=true;
}

inline void Transform::SetRotation(const quat& rotation)
{
    m_rotation = rotation;
    m_localMatrix = glm::translate(mat4(1),m_position)*mat4_cast(m_rotation)*glm::scale(mat4(1),m_scale);
    m_updateNeeded=true;
}

inline bool Transform::needUpdate() const
{
    return m_updateNeeded;
}

inline void Transform::rotateRelative(float angle, const vec3& vector)
{
    //m_rotation = glm::rotate(m_rotation, angle, vector);
    //Seem to be fucked by scaling
    m_localMatrix =  glm::rotate(m_localMatrix,angle,vector);
    m_updateNeeded=true;
}

inline void Transform::translateRelative(const vec3& move)
{
    //m_position +=move;
    //m_localMatrix = glm::translate(mat4(1),m_position)*mat4_cast(m_rotation);
    //Seem to be fucked by scaling
    m_localMatrix = glm::translate(m_localMatrix,move);
    m_updateNeeded=true;
}