#include <windows.h>
#include <exception>
#include "App.h"

INT WINAPI WinMain(HINSTANCE Instance, HINSTANCE PrevInst, LPSTR CmdLine, INT NbCmd)
{
    try
    {
        App::Instance().Run();

        App::Destroy();
	}catch(std::exception E){}


	return EXIT_SUCCESS;
}