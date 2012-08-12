#ifndef FORCE_H
#define FORCE_H

#include <AgmdPhysics\Maths\Vector3.h>

namespace AgmdPhysics
{
	class Force
	{
		Force(vec3 _vForce = vec3(0.0f), vec3 _vAppPoint = vec3(0.0f)) :
	    m_vForce(_vForce), 
		m_vAppPoint(_vAppPoint)
		{}

		void SetForce(vec3 _vForce) { m_vForce = _vForce; }
		void SetAppPoint(vec3 _vAppPoint) { m_vAppPoint = _vAppPoint; }

		vec3 GetForce() { return m_vForce; }
		vec3 GetAppPoint() { return m_vAppPoint; }


	private:
		vec3 m_vForce;
		vec3 m_vAppPoint;
	}
}

#endif // FORCE_H