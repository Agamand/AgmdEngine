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
#include <Core/Driver.h>
#include <Core/Shader/ShaderPreCompiler.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <random>
#pragma warning(disable:4496)
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


struct  TVertex
{
    vec3 position;
    a_uint32 color;
};
DeclarationPtr  declaration;
Buffer<TVertex> vertex;
Buffer<a_uint16> index;

void App::init()
{  
	printf("Loading end");

    TVertex OurVertices[] =
    {
        {vec3(0.0f, 0.5f, 0.0f), Color::red.ToABGR()},
        {vec3(0.45f, -0.5, 0.0f), Color::blue.ToABGR()},
        {vec3(-0.45f, -0.5f, 0.0f),  Color::green.ToABGR()}
    };

    a_uint16 indices[] = {
        0,1,2
    };
    Driver& driver = Driver::Get();
    vertex =  driver.CreateVertexBuffer<TVertex>(3,0,OurVertices);
    index =  driver.CreateIndexBuffer<a_uint16>(3,0,indices);
    TDeclarationElement Elements[] =
    {
        {0, ELT_USAGE_POSITION,     ELT_TYPE_FLOAT3},
        {0, ELT_USAGE_DIFFUSE,      ELT_TYPE_COLOR}

    };
    declaration =  driver.CreateVertexDeclaration(Elements);


}
void App::OnUpdate(a_uint64 time_diff/*in ms*/)
{
}

void App::OnRender3D()
{
    Driver& driver = Driver::Get();
    driver.SetDeclaration(declaration);
    driver.SetVertexBuffer(0,vertex,0,vertex.GetCount());
    driver.SetIndexBuffer(index);
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
