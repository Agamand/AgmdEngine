#ifndef _FAST2DSURFACE_H_
#define _FAST2DSURFACE_H_

#include <Config/Fwd.h>

#include <Core/Buffer/Buffer.h>
#include <Core/Declaration.h>

#include <Utilities/Singleton.h>

#include <Matrix4.h>
#include <Plane.h>

using namespace AgmdMaths;

namespace Agmd
{

    

    class Fast2DSurface : public Singleton<Fast2DSurface>
    {
        MAKE_SINGLETON(Fast2DSurface);
    public:

        
        void Draw();

    private:
        struct TVertex
        {
            vec3 position;
            vec2 t_position;
        };

        struct TMatrixBuffer
        {
            mat4 m_projection;
            mat4 m_view;
        };

        Fast2DSurface();
        ~Fast2DSurface();
        void Init();
        DeclarationPtr  m_Declaration;
        Buffer<TVertex> m_VertexBuffer;
        Buffer<short>  m_IndexBuffer;
        Buffer<TMatrixBuffer> m_MatrixBuffer;
    };
}

#endif /* _FAST2DSURFACE_H_ */
