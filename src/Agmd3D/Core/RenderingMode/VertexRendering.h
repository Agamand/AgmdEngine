/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _VERTEXRENDERING_H_
#define _VERTEXDRENDERING_H_

#include <Core/RenderingMode/RenderingMode.h>

namespace Agmd
{
    class AGMD3D_EXPORT VertexRendering : public RenderingMode
    {
    public:
        VertexRendering(int width, int height);
        VertexRendering(ivec2& screen);
        ~VertexRendering();

        virtual void compute();

        virtual void start();
        virtual void end();

    private:

    };
}

#endif /* _VERTEXRENDERING_H_ */
