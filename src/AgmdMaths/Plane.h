/*
============================================================================
AgmdMaths - Maths lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef PLANE_H
#define PLANE_H

#include <Vector3.h>
#include <Vector4.h>
#include <istream>

namespace AgmdMaths
{
    class Plane
    {
    public :	

        Plane(float a = 0.0f, float b = 0.0f, float c = 0.0f, float d = 0.0f);

        Plane(const vec3& v0, const vec3& v1, const vec3& v2);

        Plane(const vec3& normal, const vec3& point);

        void buildFromPoints(const vec3& v0, const vec3& v1, const vec3& v2);

        float distanceToPoint(const vec3& point) const;
        float distanceToPoint(const vec4& point) const;

		void normalize();

        bool operator ==(const Plane& p) const;
        bool operator !=(const Plane& p) const;

        vec3 n;
        float d;
    };

    std::istream& operator >>(std::istream& stream, Plane& plane);
    std::ostream& operator <<(std::ostream& stream, const Plane& plane);

    #include "Plane.inl"
}
#endif
