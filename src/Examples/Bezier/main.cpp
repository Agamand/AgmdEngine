/*
============================================================================
Demo - A test application !

Author : 
Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
Jean-Vincent Lamberti (https://github.com/Kinroux)

https://github.com/Agamand/AgmdEngine
status : in pause
============================================================================
*/

#include <windows.h>
#include <exception>
#include "App.h"
#include <iostream>

using namespace AgmdUtilities;
int main(int argc, char** argv)
{
    try
    {
        App::Instance().Run(argc,argv);
        App::Destroy();
    }catch(std::exception e)
    {
        std::cout << "Fail -> exception" << std::endl;
        std::cout << e.what() << std::endl;
        
    }
    system("pause");
    return EXIT_SUCCESS;
}