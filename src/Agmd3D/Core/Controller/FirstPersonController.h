/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _FIRSTPERSONCONTROLLER_H_
#define _FIRSTPERSONCONTROLLER_H_

#include <CommonDefines.h>

#include <Config/Fwd.h>
#include <Config/Export.h>

#include <Core/Controller/InputController.h>

#include <Transform.h>

using namespace AgmdMaths;

namespace Agmd
{

	class AGMD3D_EXPORT FirstPersonController : public InputController
	{
	public:
		FirstPersonController(Transform* _transform = NULL);

		virtual void onClick( int click, vec2 pos, bool up );

		virtual void onMove( vec2 pos );

		virtual void onKey( a_char key,bool up );

		virtual void update( a_uint32 timeDiff);

		void setBindTransform(Transform* transform){}
		const Transform* getTransform() const {return m_bindedTransform;}
		void updateMove();

	private:
		enum TMove
		{
			MOVE_NONE			= 0x000,
			MOVE_FORWARD		= 0x001,
			MOVE_BACK			= 0x002,
			MOVE_LEFT			= 0x004,
			MOVE_RIGHT			= 0x008,
			MOVE_UP				= 0x010,
			MOVE_DOWN			= 0x020,
			ZOOM_IN				= 0x040,
			ZOOM_OUT			= 0x080,
			ROLL_LEFT			= 0x100,
			ROLL_RIGHT			= 0x200
		};


		Transform*	m_bindedTransform;
		float		m_speed;
		a_uint32	m_moveFlags;
		vec3		_forward;
		vec3		_up;
		vec3		_left;
		vec3		_move;
	};

};


#endif /* _FIRSTPERSONCONTROLLER_H_ */