/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/Renderer.h>
#include <Matrix4.h>
#include <Debug/Logger.h>
#include <Debug/Exception.h>
#include <Debug/New.h>


namespace Agmd
{
    Renderer* Renderer::s_Instance = NULL;

    Renderer::~Renderer()
    {}

    void Renderer::Change(Renderer* newRenderer)
    {
        Destroy();

        s_Instance = newRenderer;
    }

    void Renderer::Destroy()
    {
        delete s_Instance;
        s_Instance = NULL;
    }

    Renderer& Renderer::Get()
    {
        Assert(s_Instance != NULL);

        return *s_Instance;
    }

    bool Renderer::HasCapability(TCapability cap) const
    {
        Assert(m_Capabilities.find(cap) != m_Capabilities.end());

        return m_Capabilities.find(cap)->second;
    }

    std::string Renderer::CapToString(TCapability cap) const
    {
        switch (cap)
        {
            case CAP_HW_MIPMAPPING :   return "Génération hardware des niveaux de mipmapping";
            case CAP_DXT_COMPRESSION : return "Compression de texture DXT";
            case CAP_TEX_NON_POWER_2 : return "Dimensions de textures non-puissances de 2";
            default :                  return "Fonctionnalité inconnue";
        }
    }

    void Renderer::Initialize(HWND Hwnd)
    {
        Setup(Hwnd);
        CheckCaps();

        Logger::Instance().SetFilename("Agmd3D");

        Logger::Log(LOGNORMAL,"Système de rendu : %s",GetRendererDesc().c_str());
        Logger::Log(LOGNORMAL,"Fonctionnalités supportées :");
        for (std::map<TCapability, bool>::const_iterator i = m_Capabilities.begin(); i != m_Capabilities.end(); ++i)
            Logger::Log(LOGNORMAL,"%s : %s", CapToString(i->first).c_str(), (i->second ? "OK" : "NO"));
        Logger::Log(LOGNORMAL,"Fonctionnalités proposée : \n");
        //Logger::Log(LOGNORMAL,GetExtension().c_str());
        Logger::Log(LOGNORMAL,"");
    }

    void Renderer::OnUpdate(uint64 t_diff)
    {
         Camera* cam = Camera::GetCurrent();
         if(cam)
             cam->OnUpdate(t_diff);
    }

        mat4 Renderer::GetMatView() 
        {
            return mat4(1.0f);
        }

        mat4 Renderer::GetMatProjection() 
        {
            return mat4(1.0f);
        }

        void Renderer::SetMatView(mat4 _MatView) 
        {
            //Unused function !
        }

        void Renderer::SetMatProjection(mat4 _MatProjection)
        {
            //Unused function !
        }

        void Renderer::SetScreen(ivec2 _screen)
        {
            m_Screen = _screen;
        }

        ivec2 Renderer::GetScreen()
        {
            return m_Screen;
        }

        void Renderer::SetCamera(Camera* cam)
        {
            m_Camera = cam;
        }
        Camera* Renderer::GetCamera()
        {
            return m_Camera;
        }

        void Renderer::SetTextureFlag(uint32 flag)
        {
            m_TextureFlags = flag;
        }

        void Renderer::AddTextureFlag(uint32 flag)
        {
            m_TextureFlags |= flag;
        }

        void Renderer::RemoveTextureFlag(uint32 flag)
        {
            m_TextureFlags &= ~flag;
        }

        uint32 Renderer::GetTextureFlag()
        {
            return m_TextureFlags;
        }

        void Renderer::SetActiveScene(Scene* sc)
        {
            m_ActiveScene = sc;
        }

        Scene* Renderer::GetActiveScene()
        {
            return m_ActiveScene;
        }
}