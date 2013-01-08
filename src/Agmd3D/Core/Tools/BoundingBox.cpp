#include <Core/Tools/BoundingBox.h>


namespace Agmd
{
	BoundingBox::BoundingBox()
	{
	}

	BoundingBox::~BoundingBox()
	{
	}

	vec3 BoundingBox::GetMin()
	{
		return m_min;
	}

	vec3 BoundingBox::GetMax()
	{
		return m_max;
	}
}
