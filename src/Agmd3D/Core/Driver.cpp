/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Driver.h>
#include <Matrix4.h>
#include <Debug/Logger.h>
#include <Debug/Exception.h>
#include <Debug/New.h>
#include <Core/Tools/Statistics.h>


namespace Agmd
{
    Driver* Driver::s_Instance = NULL;

    Driver::~Driver()
    {
        delete m_stats;
    }

    void Driver::Change(Driver* newRenderer)
    {
        Destroy();

        s_Instance = newRenderer;
    }

    void Driver::Destroy()
    {
        delete s_Instance;
        s_Instance = NULL;
    }

    Driver& Driver::Get()
    {
        Assert(s_Instance != NULL);

        return *s_Instance;
    }

    bool Driver::HasCapability(TCapability cap) const
    {
        Assert(m_Capabilities.find(cap) != m_Capabilities.end());

        return m_Capabilities.find(cap)->second;
    }

    std::string Driver::CapToString(TCapability cap) const
    {
        switch (cap)
        {
            case CAP_HW_MIPMAPPING :   return "Génération hardware des niveaux de mipmapping";
            case CAP_DXT_COMPRESSION : return "Compression de texture DXT";
            case CAP_TEX_NON_POWER_2 : return "Dimensions de textures non-puissances de 2";
            default :                  return "Fonctionnalité inconnue";
        }
    }

    void Driver::Initialize(HWND Hwnd)
    {
        Setup(Hwnd);
        CheckCaps();

        Logger::Instance().SetFilename("Agmd3D");
        m_stats = new Statistics();
        m_CurrentTransform = NULL;
        std::cout << "Renderer : "<< GetRendererDesc().c_str()<< std::endl;
        Logger::Log(LOGNORMAL,"Renderer : %s",GetRendererDesc().c_str());
        Logger::Log(LOGNORMAL,"Support function :");
        for (std::map<TCapability, bool>::const_iterator i = m_Capabilities.begin(); i != m_Capabilities.end(); ++i)
            Logger::Log(LOGNORMAL,"%s : %s", CapToString(i->first).c_str(), (i->second ? "OK" : "NO"));
        Logger::Log(LOGNORMAL,"Function : \n");
        //Logger::Log(LOGNORMAL,GetExtension().c_str());
        Logger::Log(LOGNORMAL,"");
    }

    void Driver::OnUpdate(a_uint64 t_diff)
    {
         //Camera* cam = Camera::getCurrent();
         //if(cam)
             //cam->onUpdate(t_diff);
    }

        mat4 Driver::GetMatView() 
        {
            return mat4(1.0f);
        }

        mat4 Driver::GetMatProjection() 
        {
            return mat4(1.0f);
        }

        void Driver::SetMatView(mat4 _MatView) 
        {
            //Unused function !
        }

        void Driver::SetMatProjection(mat4 _MatProjection)
        {
            //Unused function !
        }

        void Driver::SetScreen(ivec2 _screen)
        {
            m_Screen = _screen;
        }

        ivec2 Driver::GetScreen()
        {
            return m_Screen;
        }

        void Driver::SetCamera(Camera* cam)
        {
            m_Camera = cam;
        }
        Camera* Driver::GetCamera()
        {
            return m_Camera;
        }

        void Driver::SetTextureFlag(a_uint32 flag)
        {
            m_TextureFlags = flag;
        }

        void Driver::AddTextureFlag(a_uint32 flag)
        {
            m_TextureFlags |= flag;
        }

        void Driver::RemoveTextureFlag(a_uint32 flag)
        {
            m_TextureFlags &= ~flag;
        }

        a_uint32 Driver::GetTextureFlag()
        {
            return m_TextureFlags;
        }

        void Driver::SetActiveScene( ASceneMgr* sc )
        {
            m_ActiveScene = sc;
        }

        ASceneMgr* Driver::GetActiveScene()
        {
            return m_ActiveScene;
        }
        Statistics& Driver::GetStatistics()
        {
            return *m_stats;
        }

        float Driver::GetAspectRatio()
        {
            return ((float)m_Screen.x)/m_Screen.y;
        }
}