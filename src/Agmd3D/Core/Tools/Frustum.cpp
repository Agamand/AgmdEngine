#include <Core/Tools/Frustum.h>
#include <Core/Tools/BoundingBox.h>

SINGLETON_IMPL(Agmd::Frustum);
namespace Agmd
{
	Frustum::Frustum()
	{
	}

	Frustum::~Frustum()
	{
	} 

	void Frustum::Setup(mat4& clipMatrix)
	{
		float* clip = &clipMatrix[0][0];

		m_clipPlane[0] = Plane(clip[ 3]-clip[ 0], clip[ 7]-clip[ 4],
                    clip[11]-clip[ 8], (clip[15]-clip[12]) );

		m_clipPlane[1] = Plane( clip[ 3]+clip[ 0], clip[ 7]+clip[ 4],
						clip[11]+clip[ 8], clip[15]+clip[12] );

		m_clipPlane[2] = Plane( clip[ 3]+clip[ 1], clip[ 7]+clip[ 5],
						clip[11]+clip[ 9], clip[15]+clip[13] );

		m_clipPlane[3] = Plane( clip[ 3]-clip[ 1], clip[ 7]-clip[ 5],
						clip[11]-clip[ 9], clip[15]-clip[13] );

		m_clipPlane[4] = Plane( clip[ 3]-clip[ 2], clip[ 7]-clip[ 6],
						clip[11]-clip[10], clip[15]-clip[14] );

		m_clipPlane[5] = Plane( clip[ 3]+clip[ 2], clip[ 7]+clip[ 6],
						clip[11]+clip[10], clip[15]+clip[14] );
	for(int i = 0; i < 6; i++)
		m_clipPlane[i].Normalize();
	}

	bool Frustum::IsIn(vec3& pos)
	{
		for(int i = 0; i < 6; i++)
			if( !(m_clipPlane[i].DistanceToPoint(pos) > 0.0f) )
				return false;
		return true;
	}

	bool Frustum::IsIn(BoundingBox& box)
	{
		vec3 max,min;
		max = box.GetMax();
		min = box.GetMin();

		if( IsIn( vec3(min.x, min.y, min.z)) )
			return true;

		if( IsIn( vec3(max.x, min.y, min.z)) )
			return true;

		if( IsIn( vec3(min.x, max.y, min.z)) )
			return true;

		if( IsIn( vec3(max.x, max.y, min.z)) )
			return true;

		if( IsIn( vec3(min.x, min.y, max.z)) )
			return true;

		if( IsIn( vec3(max.x, min.y, max.z)) )
			return true;

		if( IsIn( vec3(min.x, max.y, max.z)) )
			return true;

		if( IsIn( vec3(max.x, max.y, max.z)) )
			return true;

		return false;
	}
}