/*
============================================================================
DX TEST - A test application !

Author : 
Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)

https://github.com/Agamand/AgmdEngine
status : in pause
============================================================================
*/


#include "App.h"
#include <Agmd3D/Core/MediaManager.h>
#include <Core/Shader/ShaderPreCompiler.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>

using namespace Agmd;
using namespace AgmdUtilities;

SINGLETON_IMPL(App);

BaseShaderProgram* default_program;

void App::Run(int argc, char** argv)
{
    if(argc > 0)
    {
        File main(argv[0]);
        MediaManager::Instance().AddSearchPath(main.Path());
        //ShaderPreCompiler::Instance().AddSearchPath(main.Path()+"/Shader");
    }
    AgmdApplication::Run();
}

void App::init()
{  
	printf("Loading end");
}
void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{
}

void App::OnRender3D()
{
}

void App::OnRender2D()
{
}

LRESULT CALLBACK App::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return AgmdApplication::WindowProc(hwnd,message,wParam,lParam);
}

void App::OnClick( int click, vec2 pos, bool up)
{
	AgmdApplication::OnClick(click,pos,up);
}

void App::OnMove(vec2 pos)
{
    AgmdApplication::OnMove(pos);
}	

void App::OnKey( a_char key, bool up )
{
	AgmdApplication::OnKey(key,up);
}
