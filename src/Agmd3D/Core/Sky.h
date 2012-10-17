#ifndef SKY_H
#define SKY_H



#include <Config\Fwd.h>
#include <Config\Export.h>

#include <Vector2.h>
#include <Quaternion.h>

namespace Agmd
{
	class Sky
	{
	public:
		Sky(float size = 1.0f);
		virtual ~Sky();
		
		virtual void Render() const = 0;


	protected:
		float m_fSize;
		vec3  m_vPosition;
		quat  m_qRotation;
	};
}

#endif //SKY_H