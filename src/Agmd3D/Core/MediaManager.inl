template <class T>
inline void MediaManager::RegisterLoader(Loader<T>* loader, const std::string& extensions)
{
    std::vector<std::string> ext;
    Split(extensions, ext, " /\\*.,;|-_\t\n'\"");

    SmartPtr<Loader<T> > ptr = loader;
    for (std::vector<std::string>::iterator i = ext.begin(); i != ext.end(); ++i)
        MediaHolder<T>::m_Loaders[ToLower(*i)] = ptr;
}

template <class T>
inline void MediaManager::UnregisterLoader(const std::string& extensions)
{
    std::vector<std::string> ext;
    Split(extensions, ext, " /\\*.,;|-_\t\n'\"");

    for (std::vector<std::string>::iterator i = Ext.begin(); i != Ext.end(); ++i)
        MediaHolder<T>::m_Loaders.erase(ToLower(*i));
}

template <class T>
inline T* MediaManager::LoadMediaFromFile(const File& filename) const
{
    File mediaPath = FindMedia(filename);

    T* media = FindLoader<T>(mediaPath).LoadFromFile(mediaPath.Fullname());

	Logger::Log(LOGNORMAL,"Ressource chargée : %s\n",mediaPath.Fullname().c_str());

    return media;
}

template <class T>
inline void MediaManager::SaveMediaToFile(const T* object, const File& filename) const
{
    FindLoader<T>(filename).SaveToFile(object, filename.Fullname());

    Logger::Log(LOGNORMAL,"Ressource sauvegardée : %s\n",filename.Fullname().c_str());
}

template <class T>
inline Loader<T>& MediaManager::FindLoader(const File& filename) const
{
    typename MediaHolder<T>::TLoadersMap::const_iterator itr = MediaHolder<T>::m_Loaders.find(ToLower(filename.Extension()));

    if ((itr != MediaHolder<T>::m_Loaders.end()) && itr->second)
        return *itr->second;

    throw LoadingFailed(filename.Fullname(), "Aucun loader ne prend en charge ce format de fichier");
}
