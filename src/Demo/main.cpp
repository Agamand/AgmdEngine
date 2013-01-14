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

#include <AgmdUtilities/Utilities/TinyXml/tinyxml.h>

#include <string>

using namespace AgmdUtilities;
int main(int argc, char** argv)
{
    App::Instance().Run(argc,argv);
    App::Destroy();

    return EXIT_SUCCESS;
}