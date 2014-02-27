#ifndef _RENDERINGMODE_H_
#define _RENDERINGMODE_H_

/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Vector2.h>
#include <Config/Export.h>
#include <CommonDefines.h>
#include <Core/Enums.h>
namespace Agmd
{
    class AGMD3D_EXPORT RenderingMode
    {
    public:
        RenderingMode(a_int32 width, a_int32 heigth);
        RenderingMode(ivec2& screenSize);
        
        virtual void Compute() = 0;
        void SetRenderMode(TRenderMode mode);
        static void SetRenderingMode(RenderingMode*);

        static RenderingMode* GetRenderingMode();

    protected:
        virtual void Start() = 0;
        virtual void End() = 0;
        ivec2 m_screen;
        TRenderMode m_mode;
        static RenderingMode* s_current;
    };

}

#endif /* _RENDERINGMODE_H_ */
