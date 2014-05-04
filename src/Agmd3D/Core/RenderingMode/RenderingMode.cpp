/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/RenderingMode/RenderingMode.h>
#include <Core/Driver.h>

namespace Agmd
{
    RenderingMode::RenderingMode(a_int32 width, a_int32 height) :
    m_screen(width,height),m_mode(MODE_FILL)
    {}

    RenderingMode::RenderingMode(ivec2& screensize) :
    m_screen(screensize),m_mode(MODE_FILL)
    {}

    void RenderingMode::SetRenderingMode(RenderingMode* render)
    {
        s_current = render;
    }

    RenderingMode* RenderingMode::GetRenderingMode()
    {
        return s_current;
    }

    void RenderingMode::SetRenderMode(TRenderMode mode)
    {
        m_mode = mode;
    }

    RenderingMode* RenderingMode::s_current = NULL;
}