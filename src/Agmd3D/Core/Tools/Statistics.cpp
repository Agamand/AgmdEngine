/*
============================================================================
Agmd3D - 3D Engine 
2012 - 2013
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Tools/Statistics.h>
#include <Utilities/StringUtils.h>

using namespace AgmdUtilities;

namespace Agmd
{
    Statistics::Statistics() :
        m_RenderingTime(0.0f), m_MainTime(0.0f), m_DrawCallCount(0),
        m_VertexDrawCount(0), m_TriangleDrawCount(0)
    {
    }

    void Statistics::SetRenderingTime(float time)
    {
        m_RenderingTime = time;
    }

    void Statistics::SetMainTime(float time)
    {
        m_MainTime = time;
    }

    void Statistics::SetGuiTime(float time)
    {
        m_GuiTime = time;
    }

    void Statistics::IncrDrawCall()
    {
        m_DrawCallCount++;
    }

    void Statistics::IncrVertexCount(a_uint32 count)
    {
        m_VertexDrawCount += count;
    }

    void Statistics::IncrTriangleCount(a_uint32 count)
    {
        m_TriangleDrawCount += count;
    }

    float Statistics::GetRenderingTime()
    {
        return m_RenderingTime;
    }

    float Statistics::GetMainTime()
    {
        return m_MainTime;
    }

    a_uint32 Statistics::GetFps()
    {
        return (a_uint32)(1000.0f / (float)m_MainTime);
    }

    a_uint32 Statistics::GetDrawCount()
    {
        return m_DrawCallCount;
    }

    a_uint32 Statistics::GetVertexCount()
    {
        return m_VertexDrawCount;
    }

    a_uint32 Statistics::GetTriangleCount()
    {
        return m_TriangleDrawCount;
    }

    void Statistics::ResetStatistics()
    {
        m_DrawCallCount = 0;
        m_VertexDrawCount = 0;
        m_TriangleDrawCount = 0;
    }


    std::string Statistics::ToString()
    {
        return StringBuilder("- Agmd 3D Statistics - \nMainTime : ")(m_MainTime)(" ms, RenderingTime : ")(m_RenderingTime)(" us, GuiTime : ")(m_GuiTime)(" us, fps : ")(GetFps())("\nDraw Call : ")(m_DrawCallCount)(", Vertex : ")(m_VertexDrawCount)(", Triangle :")(m_TriangleDrawCount);
    }
}
