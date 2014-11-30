#include <exception>
#include "App.h"
#include <iostream>

using namespace AgmdUtilities;

AGMD_CONSOLE_IMPL

int agmd_main(int argc, char** argv)
{

	App::Instance().Run(argc,argv);
	App::Destroy();
    return EXIT_SUCCESS;
}
