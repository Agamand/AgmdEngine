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
#include <Thread/ThreadPool.h>

AGMD_CONSOLE_IMPL



int agmd_main(int argc, char** argv)
{


    CThreadPool tpool(4);
    tpool.start();
    for(a_uint32 i = 0; i < 32; i++)
    {
		tpool.AddJob([i](){
			std::cout << i << std::endl;
		});
    }
    system("pause");

	//App::Instance().Run(argc,argv);
	//App::Destroy();
	return EXIT_SUCCESS;
}
