#ifndef VECTOR4_H
#define VECTOR4_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

#define VEC4TOSTREAM(X) X.x << " " << X.y << " " << X.z << " " << X.w
#define STREAMTOVEC4(X) X.x >> X.y >> X.z >> X.w
#define VEC4SET(V,X,Y,Z,W) V.x = X; \
                            V.y = Y; \
                            X.z = Z; \
                            X.w = W; \

namespace Agmd
{

    // INT VECTOR
    inline std::istream& operator >>(std::istream& stream, ivec4& vector)
    {
        return stream >> vector.x >> vector.y;
    }

    inline std::ostream& operator <<(std::ostream& stream, const ivec4& vector)
    {
        return stream << vector.x << " " << vector.y;
    }

    // FLOAT VECTOR
    inline std::istream& operator >>(std::istream& stream, vec4& vector)
    {
        return stream >> vector.x >> vector.y;
    }

    inline std::ostream& operator <<(std::ostream& stream, const vec4& vector)
    {
        return stream << vector.x << " " << vector.y;
    }
}

#endif
