#ifndef _VERTEXRENDERING_H_
#define _VERTEXDRENDERING_H_

#include <Core/RenderingMode/RenderingMode.h>

namespace Agmd
{
    class AGMD_EXPORT VertexRendering : public RenderingMode
    {
    public:
        VertexRendering(int width, int height);
        VertexRendering(ivec2 screen);
        ~VertexRendering();

        virtual void Compute();

        virtual void Start();
        virtual void End();

    private:

    };
}

#endif /* _VERTEXRENDERING_H_ */
