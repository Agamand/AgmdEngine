#ifndef DYNAMICCAMERA_H
#define DYNAMICCAMERA_H

#include <Core\Camera\Camera.h>

namespace Agmd
{

	class AGMD_EXPORT DynamicCamera : public Camera
	{
	public:
		DynamicCamera(vec3 pos = vec3());
		virtual ~DynamicCamera();

		virtual void OnUpdate(uint64 time_diff);

		virtual void OnMouseMotion(int x, int y);

		virtual void OnKeyboard(char key, bool up);

		virtual void OnMouseWheel(float delta);

		virtual mat4 look();

		void setLinkTransfo(TransformPtr _transfo);



	protected:

		virtual void VectorsFromAngles();
		TransformPtr m_transfo;
	};
}

#endif //FPCAMERA_H
