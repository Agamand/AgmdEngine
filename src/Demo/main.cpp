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
#include <exception>
#include "App.h"
#include "Test/Circle.h"
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

    /*Circle c1(Point(0,0),5);
    Circle c2(Point(0,6),1);
    Point p(0,1);
    std::cout <<"c1"<< c1<< std::endl;
    std::cout <<"c2"<< c2<< std::endl;
    std::cout <<"c3"<< p<< std::endl;
    
    std::cout << "p1 in c1 : " << c1.include(p) << std::endl;
    std::cout << "p1 in c2 : " << c2.include(p) << std::endl;
    std::cout << "c1 intesect c2 : " << c1.intersect(c2) << std::endl;
    system("pause");*/
    system("pause");
    return EXIT_SUCCESS;
}