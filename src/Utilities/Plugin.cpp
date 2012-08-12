#include <Utilities\Plugin.h>


namespace Agmd
{
	Plugin::Plugin(const std::string& Filename)
	{
		m_Library = LoadLibrary(Filename.c_str());
		if (!m_Library)
			throw LoadingFailed(Filename, "Impossible de charger la biblioth�que dynamique");

		PtrFunc LoadFunc = reinterpret_cast<PtrFunc>(GetProcAddress(m_Library, "LoadPlugin"));
		if (!LoadFunc)
			throw LoadingFailed(Filename, "Impossible de trouver la fonction 'LoadPlugin' dans la biblioth�que dynamique");

		LoadFunc();
	}

	Plugin::~Plugin()
	{
		PtrFunc UnloadFunc = reinterpret_cast<PtrFunc>(GetProcAddress(m_Library, "UnloadPlugin"));
		if (!UnloadFunc)
			throw LoadingFailed("Module", "Impossible de trouver la fonction 'UnloadPlugin' dans la biblioth�que dynamique");

		UnloadFunc();

		if (m_Library)
			FreeLibrary(m_Library);
	}
}