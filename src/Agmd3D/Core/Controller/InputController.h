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
#include <Core/AgmdApplication.h>

#include <Vector2.h>
namespace Agmd
{

	class AGMD3D_EXPORT InputController : public Controller, public AgmdApplication::InputListener
	{
	public:
		InputController(): Controller(){};
	};

}


#endif /* _INPUTCONTROLLER_H_ */