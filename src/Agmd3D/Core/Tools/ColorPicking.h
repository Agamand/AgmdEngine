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
        ColorPicking();
        SceneNode* pick(const vec3& position,const vec3& ray);
        SceneNode* pick(const vec2& pos);
        Texture& getPickingScreen();
        ShaderProgram m_picking_shader;
    private:
        FrameBuffer* m_framebuffer;
        RenderBuffer* m_depth;
        Texture m_pickingScreen;
    }; 
}
#endif /* _COLORPICKING_H_ */
