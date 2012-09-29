#ifndef FPCAMERA_H
#define FPCAMERA_H

#include <Core\Camera\Camera.h>

namespace Agmd
{

	class FPCamera : public Camera
	{
	public:
		FPCamera(vec3 pos = vec3());
		virtual ~FPCamera();

		virtual void OnUpdate(uint64 time_diff);

		virtual void OnMouseMotion(int x, int y);

		virtual void OnKeyboard(char key, bool up);

		virtual void OnMouseWheel(float delta);

	protected:
		virtual void VectorsFromAngles();

		float _theta;
		float _phi;
	};
}

#endif //FPCAMERA_H
