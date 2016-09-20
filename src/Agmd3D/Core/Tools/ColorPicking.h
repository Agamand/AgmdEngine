/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _COLORPICKING_H_
#define _COLORPICKING_H_

#include <Core/SceneNode/SceneNode.h>
#include <Core/Buffer/FrameBuffer.h>
#include <Core/Buffer/RenderBuffer.h>
#include <Core/Texture/Texture.h>
#include <Core/Shader/ShaderProgram.h>

#include <Utilities/Singleton.h>
#include <Config/Export.h>
#include <CommonDefines.h>

namespace Agmd
{
    class AGMD3D_EXPORT ColorPicking: public Singleton<ColorPicking>
    {
        MAKE_SINGLETON(ColorPicking)
    public:
        struct PickingResult
        {
            PickingResult() : node(NULL)
            {
            }

            SceneNode* node;
            vec3 ray;
            vec3 hitPosition;
        };

        ColorPicking();
        PickingResult pick(const vec3& position, const vec3& ray);
        PickingResult pick(const vec2& pos);
        Texture& getPickingScreen();
        ShaderProgram m_picking_shader;
    private:
        FrameBuffer* m_framebuffer;
        Texture m_pickingScreen;
        Texture m_depth;
    };
}
#endif /* _COLORPICKING_H_ */
