
#ifndef SINGLETON_H
#define SINGLETON_H

#include <cstdlib>
#include <Debug/New.h>


namespace Agmd
{
    template <class T>
    class Singleton
    {
    public :

        static T& Instance()
        {
            if (!Inst)
                Inst = new T;

            return *Inst;
        }

        static void Destroy()
        {
            delete Inst;
            Inst = NULL;
        }

    protected :
        Singleton() {}
        ~Singleton() {}
    private :

        static T* Inst;

        Singleton(const Singleton&);
        Singleton& operator =(const Singleton&);
    };

    #include <Debug/NewOff.h>

    #define MAKE_SINGLETON(Class) \
        public : \
            friend class Agmd::Singleton<Class>; \
            static Class& Instance(); \
        private :

    #define SINGLETON_IMPL(Class) \
        template <> Class* Agmd::Singleton<Class>::Inst = NULL; \
        Class& Class::Instance() \
        { \
            return Agmd::Singleton<Class>::Instance(); \
        } \

}

#endif // SINGLETON_H