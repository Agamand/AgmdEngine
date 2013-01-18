/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/RenderingMode/RenderingMode.h>


namespace Agmd
{
    RenderingMode::RenderingMode(int32 width, int32 height) :
    m_screen(width,height)
    {}

    RenderingMode::RenderingMode(ivec2& screensize) :
    m_screen(screensize)
    {}

    void RenderingMode::SetRenderingMode(RenderingMode* render)
    {
        s_current = render;
    }

    RenderingMode* RenderingMode::GetRenderingMode()
    {
        return s_current;
    }

    RenderingMode* RenderingMode::s_current = NULL;
}