/*
============================================================================
Agmd3D - 3D Engine
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

template <class T>
inline void MediaManager::RegisterLoader(Loader<T>* loader, const std::string& extensions)
{
    a_vector<std::string> ext;
    Split(extensions, ext, " /\\*.,;|-_\t\n'\"");

    SmartPtr<Loader<T> > ptr = loader;
	for(a_uint32 i = 0, len =ext.size(); i < len; i++)
		MediaHolder<T>::m_Loaders[ToLower(ext[i])] = ptr;
}

template <class T>
inline void MediaManager::UnregisterLoader(const std::string& extensions)
{
    a_vector<std::string> ext;
    Split(extensions, ext, " /\\*.,;|-_\t\n'\"");

	for(a_uint32 i = 0, len =ext.size(); i < len; i++)
		MediaHolder<T>::m_Loaders.erase(ToLower(ext[i]));

}

template <class T>
inline T* MediaManager::LoadMediaFromFile(const File& filename) const
{
    File mediaPath = FindMedia(filename);

    T* media = FindLoader<T>(mediaPath).LoadFromFile(mediaPath.Fullname());

    Logger::Log(LOGNORMAL,"Ressource chargée : %s",mediaPath.Fullname().c_str());

    return media;
}

template <class T>
inline void MediaManager::SaveMediaToFile(const T* object, const File& filename) const
{
    FindLoader<T>(filename).SaveToFile(object, filename.Fullname());

    Logger::Log(LOGNORMAL,"Ressource sauvegardée : %s",filename.Fullname().c_str());
}

template <class T>
inline Loader<T>& MediaManager::FindLoader(const File& filename) const
{
    typename MediaHolder<T>::TLoadersMap::const_iterator itr = MediaHolder<T>::m_Loaders.find(ToLower(filename.Extension()));

    if ((itr != MediaHolder<T>::m_Loaders.end()) && itr->second)
        return *itr->second;

    throw LoadingFailed(filename.Fullname(), "Aucun loader ne prend en charge ce format de fichier");
}
