/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Tools/ColorPicking.h>
#include <Core/Driver.h>
#include <Core/Model/SceneMgr.h>
#include <Core/Texture/Image.h>
#include <Core/Tools/Fast2DSurface.h>

SINGLETON_IMPL(Agmd::ColorPicking);


#define SCREEN_SPACE 1
namespace Agmd
{

    ColorPicking::ColorPicking()
    {
        m_framebuffer = Driver::Get().CreateFrameBuffer();
        m_depth = Driver::Get().CreateRenderBuffer(ivec2(SCREEN_SPACE),PXF_DEPTH);
        m_pickingScreen.Create(ivec2(SCREEN_SPACE),PXF_A8R8G8B8,TEXTURE_2D);
        m_framebuffer->SetTexture(m_pickingScreen,COLOR_ATTACHMENT);
        m_framebuffer->SetRender(m_depth,DEPTH_ATTACHMENT);
        m_picking_shader.LoadFromFile("/Shader/core/picking.glsl");
    }
    SceneNode* ColorPicking::pick(const vec2& screen){ //screen (0,0) to (1,1);
        vec3 ray,positon;

        Camera* cam = Camera::getCurrent(CAMERA_3D);
        SceneNode* node = cam->getNode();
        vec3 start(screen,0);
        vec3 end(screen,1);
        if(node && cam->unProject(start) &&    cam->unProject(end))
        {
            end.y = end.y;
            start.y = start.y;
            return pick(start,normalize(end-start));
        }else return NULL;
        
    }
    SceneNode* ColorPicking::pick( const vec3& position,const vec3& ray )
    {
        vec3 _ray(ray.x,ray.y,ray.z); //WHY?
        printf("positon %f %f %f,",position.x,position.y,position.z);
        printf(" ray %f %f %f\n",_ray.x,_ray.y,_ray.z);
        //mat4 d = lookAt(vec3(0,0,0),vec3(0,0,-1),vec3(0,1,0));
        mat4 proj = ortho(-0.1f,0.1f,-0.1f,0.1f,0.01f,1000.f)*lookAt(position,position+_ray,vec3(0,1,0));
        Driver& driver = Driver::Get();
        SceneMgr* sc = driver.GetActiveScene();
        sc->Compute();
        const RenderQueue& queue = sc->getRenderQueue();
        const a_vector<DisplayNode*>& displayable = queue.getDisplayable();
        const a_vector<DisplayNode*>& displayable2 = queue.getDisplayable(TYPE_BLEND);
        driver.SetViewPort(ivec2(0),ivec2(SCREEN_SPACE));
        m_framebuffer->Clear();
        m_framebuffer->Bind();
        driver.SetCurrentProgram(m_picking_shader.GetShaderProgram());
        m_picking_shader.SetParameter("u_matProjection",proj);
        //Fast2DSurface::Instance().Draw();
        driver.Enable(TRenderParameter::RENDER_ZTEST,true);
        driver.Enable(TRenderParameter::RENDER_ZWRITE,true);
        Color test_Color[3] = {Color::red,Color::green,Color::blue};
        for(a_uint32 i =0; i < displayable.size(); ++i){
            DisplayNode* n = displayable[i];
            a_uint32 icolor = i+1;//test_Color[i%3].ToABGR();
            a_uint8* color =(a_uint8*)&icolor;
             
            m_picking_shader.SetParameter("u_color",vec4(color[0]/255.f,color[1]/255.f,color[2]/255.f,color[3]/255.f));
            n->draw();
        }
        for(a_uint32 i =0; i < displayable2.size(); ++i){
            DisplayNode* n = displayable2[i];
            a_uint32 icolor = (displayable.size()+i)+1;//test_Color[i%3].ToABGR();
            a_uint8* color =(a_uint8*)&icolor;

            m_picking_shader.SetParameter("u_color",vec4(color[0]/255.f,color[1]/255.f,color[2]/255.f,color[3]/255.f));
            n->draw();
        }
        driver.SetCurrentProgram(NULL);
        m_framebuffer->UnBind();
        m_pickingScreen.updatePixelFromTexture();
        Image& p = m_pickingScreen.GetPixels();
        //printf("ID %i\n",*((int*)p.GetData()));
        
        a_uint32 index = *((int*)p.GetData());
        
        if(index > 0 && index-1 < displayable.size())
            return displayable[index-1];
        
        if(index >= displayable.size() && index-1-displayable.size() < displayable2.size())
                return displayable2[index-1-displayable.size()];
        return NULL;
    }

    Texture& ColorPicking::getPickingScreen()
    {
        return m_pickingScreen;
    }



}
