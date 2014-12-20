/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _INPUTCONTROLLER_H_
#define _INPUTCONTROLLER_H_

#include <CommonDefines.h>

#include <Config/Fwd.h>
#include <Config/Export.h>

#include <Core/Controller/Controller.h>

#include <Vector2.h>
namespace Agmd
{

	class AGMD3D_EXPORT InputController : public Controller
	{
	public:
		InputController();
		virtual void onClick(int click, vec2 pos, bool up) = 0;
		virtual void onMove(vec2 pos) = 0;
		virtual void onKey(a_char key,bool up) = 0;
	};

}


#endif /* _INPUTCONTROLLER_H_ */