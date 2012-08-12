
#ifndef ENTITIES_H
#define ENTITIES_H

#include <AgmdPhysics\Maths\Vector3.h>
#include <AgmdPhysics\Core\Force.h>

#include <vector>

namespace AgmdPhysics
{

	typedef std::vector<Force> ForceVector;

	class Entities
	{
	public:


		void ClearAllForces();

	private:
		float		m_fMass;			// Mass
		vec3		m_vPosition;		// Position
		vec3		m_vVelocity;		// Velocity
		vec3		m_vAcceleration;	// Acceleration
		ForceVector m_fvForces;			// Force sum;

		
	}

}

#endif // ENTITIES_H