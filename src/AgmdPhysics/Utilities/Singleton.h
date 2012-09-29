
#ifndef SINGLETON_H
#define SINGLETON_H

#include <cstdlib>

namespace AgmdPhysics
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

    #define MAKE_SINGLETON(Class) \
        public : \
            friend class AgmdPhysics::Singleton<Class>; \
            static Class& Instance(); \
        private :

    #define SINGLETON_IMPL(Class) \
        template <> Class* AgmdPhysics::Singleton<Class>::Inst = NULL; \
        Class& Class::Instance() \
        { \
            return AgmdPhysics::Singleton<Class>::Instance(); \
        } \

}

#endif // SINGLETON_H