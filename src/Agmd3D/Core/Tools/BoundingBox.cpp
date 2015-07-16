/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Tools/BoundingBox.h>

#include <CommonDefines.h>
namespace Agmd
{

    BoundingBox::BoundingBox(const a_vector<vec3>& vertex_pos) : m_min(0),m_max(0)
    {
        if(!vertex_pos.size())
            return;
        m_min = m_max = vertex_pos[0];
        for(a_uint32 i = 1,len = vertex_pos.size(); i < len; i++ )
        {
            m_min.x = min(m_min.x,vertex_pos[i].x);
            m_min.y = min(m_min.y,vertex_pos[i].y);
            m_min.z = min(m_min.z,vertex_pos[i].z);

            m_max.x = max(m_max.x,vertex_pos[i].x);
            m_max.y = max(m_max.y,vertex_pos[i].y);
            m_max.z = max(m_max.z,vertex_pos[i].z);
        }
    }

    BoundingBox::BoundingBox(const vec3& min, const vec3& max) : m_min(min),m_max(max)
    {}

    BoundingBox::BoundingBox(): m_min(0),m_max(0)
    {}

	BoundingBox::BoundingBox( const BoundingBox& bbox ):
		m_min(bbox.m_min),
		m_max(bbox.m_max)
	{

	}

    vec3 BoundingBox::GetMin() const
    {
        return m_min;
    }

    vec3 BoundingBox::GetMax() const
    {
        return m_max;
    }

    const BoundingBox BoundingBox::getTransformedBoundingBox( const mat4& mat ) const
    {
        vec3 _min = m_min,
            _max = m_max;
        vec4 points_box[8] = {
            vec4(_min,1),
            vec4(_max,1),
            vec4(_max.x,_min.y,_min.z,1),
            vec4(_min.x,_max.y,_min.z,1),
            vec4(_max.x,_max.y,_min.z,1),
            vec4(_min.x,_min.y,_max.z,1),
            vec4(_min.x,_max.y,_max.z,1),
            vec4(_max.x,_min.y,_max.z,1)
        };
        for(a_uint8 i = 1; i < 8; i++)
            points_box[i] = mat*points_box[i];

        _min = _max = vec3(points_box[0]);
        for(a_uint8 i = 1; i < 8; i++)
        {
            _min.x = min(_min.x,points_box[i].x);
            _min.y = min(_min.y,points_box[i].y);
            _min.z = min(_min.z,points_box[i].z);

            _max.x = max(_max.x,points_box[i].x);
            _max.y = max(_max.y,points_box[i].y);
            _max.z = max(_max.z,points_box[i].z);
        }
        return BoundingBox(_min,_max);
    }

    void BoundingBox::mult( const mat4& matrix, const BoundingBox& bbox )
    {
        vec3 _min = bbox.GetMin(),
        _max = bbox.GetMax();
        vec4 points_box[8] = {
            vec4(_min,1),
            vec4(_max,1),
            vec4(_max.x,_min.y,_min.z,1),
            vec4(_min.x,_max.y,_min.z,1),
            vec4(_max.x,_max.y,_min.z,1),
            vec4(_min.x,_min.y,_max.z,1),
            vec4(_min.x,_max.y,_max.z,1),
            vec4(_max.x,_min.y,_max.z,1)
        };
        for(a_uint8 i = 1; i < 8; i++)
            points_box[i] = matrix*points_box[i];

        m_min = m_max = vec3(points_box[0]);
        for(a_uint8 i = 1; i < 8; i++)
        {
            m_min.x = min(m_min.x,points_box[i].x);
            m_min.y = min(m_min.y,points_box[i].y);
            m_min.z = min(m_min.z,points_box[i].z);

            m_max.x = max(m_max.x,points_box[i].x);
            m_max.y = max(m_max.y,points_box[i].y);
            m_max.z = max(m_max.z,points_box[i].z);
        }
    }

	BoundingBox BoundingBox::operator/( float value ) const
	{
		float _length = length(m_max-m_min)/2.0f;
		vec3 center = GetCenter(),
			 dir = normalize(m_max-m_min),
			 _min(center-_length/value*dir),
			 _max(center+_length/value*dir);
		return BoundingBox(_min,_max);
	}

	Agmd::BoundingBox BoundingBox::operator*( float value ) const
	{
		float _length = length(m_max-m_min);
		vec3 center = GetCenter(),
			dir = normalize(m_max-m_min),
			_min(center-_length*value*dir),
			_max(center+_length*value*dir);
		return BoundingBox(_min,_max);
	}

	glm::vec3 BoundingBox::GetCenter() const
	{
		return m_min+(m_max-m_min)/2.f;
	}

	BoundingBox& BoundingBox::operator+=( vec3 translate )
	{
		this->m_max+=translate;
		this->m_min+=translate;
		return *this;
	}



	bool BoundingBox::Within( BoundingSphere& bsphere )
	{
		vec3 _min(bsphere.GetCenter()-vec3(bsphere.GetRadius())),
			 _max(bsphere.GetCenter()+vec3(bsphere.GetRadius()));


		return m_min.x <= _min.x && m_min.y <= _min.y && m_min.z <= _min.z
			&& m_max.x >= _max.x && m_max.y >= _max.y && m_max.z >= _max.z;

	}

}
