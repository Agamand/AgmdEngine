#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <Vector3.h>
#include <Matrix4.h>

namespace Agmd
{
	class Light
	{
	public:
		Light(vec3 pos);

		~Light();

	private:
		float m_angle;
		vec4 m_position;
		vec3 m_ambient;
		vec3 m_specular;
		vec3 m_diffuse;

	};
}

#endif /* _LIGHT_H_ */