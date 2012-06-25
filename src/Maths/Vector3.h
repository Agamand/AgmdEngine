#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

#define VEC3TOSTREAM(X) X.x << " " << X.y << " " << X.z 
#define STREAMTOVEC3(X) X.x >> X.y >> X.z
#define VEC3SET(V,X,Y,Z) V.x = X; \
						  V.y = Y; \
						  V.z = Z; \

namespace Agmd
{

	// INT VECTOR
	inline std::istream& operator >>(std::istream& stream, ivec3& vector)
	{
		return stream >> vector.x >> vector.y;
	}

	inline std::ostream& operator <<(std::ostream& stream, const ivec3& vector)
	{
		return stream << vector.x << " " << vector.y;
	}

	// FLOAT VECTOR
	inline std::istream& operator >>(std::istream& stream, vec3& vector)
	{
		return stream >> vector.x >> vector.y;
	}

	inline std::ostream& operator <<(std::ostream& stream, const vec3& vector)
	{
		return stream << vector.x << " " << vector.y;
	}
}

#endif
