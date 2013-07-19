/*
============================================================================
Agmd3D - 3D Engine 
2012 - 2013
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _STATISTICS_H_
#define _STATISTICS_H_


#include <Config/Export.h>
#include <CommonDefines.h>
#include <string>

namespace Agmd
{
    class AGMD3D_EXPORT Statistics
    {
    public:

        Statistics();

        void SetRenderingTime(float time);
        void SetMainTime(float time);
        void SetGuiTime(float time);
        void IncrDrawCall();
        void IncrVertexCount(uint32 count);
        void IncrTriangleCount(uint32 count);
        float GetRenderingTime();
        float GetMainTime();
        uint32 GetFps();
        uint32 GetDrawCount();
        uint32 GetVertexCount();
        uint32 GetTriangleCount();

        void ResetStatistics();
        std::string ToString();
    private:
        float m_RenderingTime; // in Ms
        float m_MainTime; // global time for every frame, in Ms (include RenderingTime)
        float m_GuiTime;
        uint32 m_DrawCallCount; // count of draw for one frame
        uint32 m_VertexDrawCount; // count of vertex draw for oneframe
        uint32 m_TriangleDrawCount; // count of triangles draw for one frame
    };
}

#endif /* _STATISTICS_H_ */