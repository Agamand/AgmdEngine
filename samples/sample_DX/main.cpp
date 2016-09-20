/*
============================================================================


Author : 
Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)

https://github.com/Agamand/AgmdEngine
status : in pause
============================================================================
*/
#include <exception>
#include "App.h"
#include <iostream>

AGMD_CONSOLE_IMPL


int agmd_main(int argc, char** argv)
{
	App::Instance().Run(argc,argv);
	App::Destroy();
	return EXIT_SUCCESS;
}
