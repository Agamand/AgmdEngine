#ifndef MEDIAMANAGER_H
#define MEDIAMANAGER_H

#include <Utilities/Singleton.h>
#include <Utilities/GenHierarchies.h>
#include <Utilities/File.h>
#include <Utilities/StringUtils.h>
#include <Utilities/SmartPtr.h>
#include <Core/Loader.h>
#include <Core/SceneObject/Model.h>
#include <Core/Texture/Image.h>
#include <Debug/Exception.h>
#include <Debug/Logger.h>
#include <algorithm>
#include <cctype>
#include <map>
#include <set>
#include <string>
#include <Debug/New.h>


namespace Agmd
{
    typedef TYPELIST_4(Model, Image, BaseShader, BaseShaderProgram) MediaList;

    template <class T>
    struct MediaHolder
    {
        typedef std::map<std::string, SmartPtr<Loader<T> > > TLoadersMap;
        TLoadersMap m_Loaders;
    };

    class AGMD_EXPORT MediaManager : public Singleton<MediaManager>, public ScatteredHierarchy<MediaList, MediaHolder>
    {

    MAKE_SINGLETON(MediaManager)

    public :

        void AddSearchPath(const std::string& path);

        template <class T> void RegisterLoader(Loader<T>* loader, const std::string& ext);

        template <class T> void UnregisterLoader(const std::string& ext);

        template <class T> T* LoadMediaFromFile(const File& filename) const;

        template <class T> void SaveMediaToFile(const T* object, const File& filename) const;

    private :

        MediaManager();

        ~MediaManager();

        File FindMedia(const File& filename) const;

        template <class T> Loader<T>& FindLoader(const File& filename) const;

        std::set<std::string> m_Paths;
    };

    #include "MediaManager.inl"
    #include <Debug/NewOff.h>

}


#endif //MEDIAMANAGER_H
