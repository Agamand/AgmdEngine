/*
============================================================================
AgmdMaths - Maths lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

inline Plane::Plane(float a, float b, float c, float _d) :
n(a, b, c),
d(_d)
{}

inline Plane::Plane(const vec3& v0, const vec3& v1, const vec3& v2)
{
    BuildFromPoints(v0, v1, v2);
}

inline Plane::Plane(const vec3& normal, const vec3& point) :
n(normal),
d(length(point))
{}

inline void Plane::BuildFromPoints(const vec3& v0, const vec3& v1, const vec3& v2)
{
    n = cross(v1 - v0, v2 - v0);
    normalize(n);

    d = -dot(n, v0);
}

inline float Plane::DistanceToPoint(const vec3& point) const
{
    return dot(n, point) + d;
}

inline float Plane::DistanceToPoint(const vec4& point) const
{
    return n.x * point.x + n.y * point.y + n.z * point.z + d * point.w;
}

inline void Plane::Normalize()
{
    d /= length(n);
    n = normalize(n);
}

inline bool Plane::operator ==(const Plane& p) const
{
    return ((n == p.n) && (fabs(d - p.d) <= std::numeric_limits<float>::epsilon()));
}

inline bool Plane::operator !=(const Plane& p) const
{
    return !(*this == p);
}

inline std::istream& operator >>(std::istream& stream, Plane& plane)
{
    return stream >> plane.n >> plane.d;
}

inline std::ostream& operator <<(std::ostream& stream, const Plane& plane)
{
    return stream << plane.n << " " << plane.d;
}

