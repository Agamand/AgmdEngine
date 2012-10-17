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
		//Logger::Log(LOGNORMAL,"Fonctionnalités proposée :");
		//Logger::Log(LOGNORMAL,"%s",GetExtension().c_str());
		Logger::Log(LOGNORMAL,"Constante interface :");
		Logger::Log(LOGNORMAL,"%s",GetConstant().c_str());
		Logger::Log(LOGNORMAL,"");
	}

		mat4 Renderer::GetMatView() 
		{
			return m_MatView;
		}

		mat4 Renderer::GetMatProjection() 
		{
			return m_MatProjection;
		}

		void Renderer::SetMatView(mat4 _MatView) 
		{
			m_MatView = _MatView;
			_LoadMatrix(MAT_VIEW, m_MatView);
		}

		void Renderer::SetMatProjection(mat4 _MatProjection)
		{
			m_MatProjection = _MatProjection;
			_LoadMatrix(MAT_PROJECTION, m_MatProjection);
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
		Camera* Renderer::getCamera()
		{
			return m_Camera;
		}
}