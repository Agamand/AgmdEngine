#include <Core/SceneObject/Displayable.h>


namespace Agmd
{
	Displayable::Displayable()
	{}

	Displayable::~Displayable()
	{}

	void Displayable::Rotate(float angle, vec3 vector)
	{
		m_transform.m_rotation = quat(rotate(m_transform.m_rotation, angle, vector));
	}

	void Displayable::SetRotation(mat4 mat)
	{
		m_transform.m_rotation = quat(mat);
	}
	
	void Displayable::Move(vec3 move)
	{
		m_transform.m_position += move;
	}

	void Displayable::Move(float move_x, float move_y, float move_z)
	{
		m_transform.m_position += vec3(move_x, move_y, move_z);
	}

	void Displayable::MoveTo(vec3 pos)
	{
		m_transform.m_position = pos;
	}

	void Displayable::MoveTo(float pos_x, float pos_y, float pos_z)
	{
		m_transform.m_position = vec3(pos_x, pos_y, pos_z);
	}

	vec3 Displayable::getTranslate() 
	{
		return m_transform.m_position;
	}

	mat4 Displayable::getRotate() 
	{
		return mat4_cast(m_transform.m_rotation);
	}

	Transform& Displayable::getPosition() 
	{ 
		return m_transform;
	}
}

