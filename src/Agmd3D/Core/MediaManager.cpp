/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#include <Core/MediaManager.h>
#include <Debug/New.h>

SINGLETON_IMPL(Agmd::MediaManager);

namespace Agmd
{



    MediaManager::MediaManager()
    {
        m_Paths.insert("");
    }

    MediaManager::~MediaManager()
    {}

    void MediaManager::AddSearchPath(const std::string& path)
    {
        if (path.empty() || (*path.rbegin() == '\\') || (*path.rbegin() == '/'))
            m_Paths.insert(path);
        else
            m_Paths.insert(path + "\\");
    }

    File MediaManager::FindMedia(const File& filename) const
    {
        for (std::set<std::string>::const_iterator itr = m_Paths.begin(); itr != m_Paths.end(); ++itr)
        {
            File retFile = *itr + filename.Fullname();
            if (retFile.Exists())
                return retFile;
        }

        throw LoadingFailed(filename.Fullname(), "Fichier introuvable dans les répertoires de recherche");
    }

}
