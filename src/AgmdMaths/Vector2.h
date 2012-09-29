#ifndef VECTOR2_H
#define VECTOR2_H

#include <limits>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;


#define VEC2TOSTREAM(X) X.x << " " <<X.y
#define STREAMTOVEC2(X) X.x >> X.y
#define VEC2SET(V,X,Y) V.x = X; \
						V.y = Y; \

namespace AgmdMaths
{

	// INT VECTOR
	inline std::istream& operator >>(std::istream& stream, ivec2& vector)
	{
		return stream >> vector.x >> vector.y;
	}

	inline std::ostream& operator <<(std::ostream& stream, const ivec2& vector)
	{
		return stream << vector.x << " " << vector.y;
	}

	// FLOAT VECTOR
	inline std::istream& operator >>(std::istream& stream, vec2& vector)
	{
		return stream >> vector.x >> vector.y;
	}

	inline std::ostream& operator <<(std::ostream& stream, const vec2& vector)
	{
		return stream << vector.x << " " << vector.y;
	}
}

#endif
