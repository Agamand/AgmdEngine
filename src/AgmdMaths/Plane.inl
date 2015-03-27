/*
============================================================================
AgmdMaths - Maths lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/
#define FABS(x) (x>=0?x:-x)
inline Plane::Plane(float a, float b, float c, float _d) :
n(a, b, c),
d(_d)
{}

inline Plane::Plane(const vec3& v0, const vec3& v1, const vec3& v2)
{
    buildFromPoints(v0, v1, v2);
}

inline Plane::Plane(const vec3& normal, const vec3& point) :
n(normal),
d(-glm::dot(normal,point))
{}

inline void Plane::buildFromPoints(const vec3& v0, const vec3& v1, const vec3& v2)
{
    n = cross(v1 - v0, v2 - v0);
    glm::normalize(n);

    d = -dot(n, v0);
}

inline float Plane::distanceToPoint(const vec3& point) const
{
    return dot(n, point) + d;
}

inline float Plane::distanceToPoint(const vec4& point) const
{
    return n.x * point.x + n.y * point.y + n.z * point.z + d * point.w;
}

inline void Plane::normalize()
{
    d /= length(n);
    n = glm::normalize(n);
}

inline bool Plane::operator ==(const Plane& p) const
{
    return ((n == p.n) && (fabs(d - p.d) <= std::numeric_limits<float>::epsilon()));
}

inline bool Plane::operator !=(const Plane& p) const
{
    return !(*this == p);
}

inline bool Plane::intersect(vec3 start, vec3 dir,vec3& res)
{
    if(FABS(glm::dot(dir,n)) < 0.0001f)
        return false;

    float _d = d;
    float _C = glm::dot(n,dir);
    float C = glm::dot(n,start) + _d;

    float k = -C/_C;

    res = dir*k + start;
    return true;
}

inline std::istream& operator >>(std::istream& stream, Plane& plane)
{
    return stream >> plane.n >> plane.d;
}

inline std::ostream& operator <<(std::ostream& stream, const Plane& plane)
{
    return stream << plane.n << " " << plane.d;
}

