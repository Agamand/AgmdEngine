#include <windows.h>
#include <exception>
#include "App.h"

int main(int argc, char** argv)
{
    try
    {
        App::Instance().Run(argc,argv);

        App::Destroy();
	}catch(std::exception E){}


	return EXIT_SUCCESS;
}