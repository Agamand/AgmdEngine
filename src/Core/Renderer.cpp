#include <Core/Renderer.h>
#include <Maths/Matrix4.h>
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

		Logger::Log(LOGNORMAL,"Système de rendu : %s\n",GetRendererDesc());
		Logger::Log(LOGNORMAL,"Fonctionnalités supportées :\n");
		for (std::map<TCapability, bool>::const_iterator i = m_Capabilities.begin(); i != m_Capabilities.end(); ++i)
			Logger::Log(LOGNORMAL,"    %s : %s", CapToString(i->first), (i->second ? "OK" : "NO"));
		Logger::Log(LOGNORMAL,"\n");
	}
}