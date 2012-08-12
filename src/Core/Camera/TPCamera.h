#ifndef TPCAMERA_H
#define TPCAMERA_H

#include <Core\Camera\Camera.h>

namespace Agmd
{

	class TPCamera : public Camera
	{
	public:
		TPCamera(vec3 pos = vec3());
		virtual ~TPCamera();

		virtual void OnUpdate(uint64 time_diff);

		virtual void OnMouseMotion(int x, int y);

		virtual void OnKeyboard(char key, bool up);
	protected:
		virtual void VectorsFromAngles();

		float _theta;
		float _phi;
		float distance;
	};
}

#endif //TPCAMERA_H