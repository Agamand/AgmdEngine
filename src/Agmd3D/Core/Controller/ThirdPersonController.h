/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _THIRDPERSONCONTROLLER_H_
#define _THIRDPERSONCONTROLLER_H_

#include <CommonDefines.h>

#include <Config/Fwd.h>
#include <Config/Export.h>

#include <Core/Controller/InputController.h>

namespace Agmd
{

	class AGMD3D_EXPORT ThirdPersonController: public InputController
	{
	public:
		ThirdPersonController();

	};

}


#endif /* _THIRDPERSONCONTROLLER_H_ */