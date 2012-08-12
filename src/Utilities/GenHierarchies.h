#ifndef GENHIERARCHIES_H
#define GENHIERARCHIES_H

#include <Utilities/Typelist.h>


namespace Agmd
{
    template <class TList, template <class> class Handler> class ScatteredHierarchy;

    template
    <
        class T1,
        class T2,
        template <class> class Handler
    >
    class ScatteredHierarchy<TypeList<T1, T2>, Handler> : public Handler<T1>, public ScatteredHierarchy<T2, Handler>
    {
    };

    template
    <
        class T,
        template <class> class Handler
    >
    class ScatteredHierarchy<TypeList<T, NullType>, Handler> : public Handler<T>
    {
    };

    template
    <
        template <class> class Handler
    >
    class ScatteredHierarchy<NullType, Handler>
    {
    };

    template <class TList, template <class, class> class Handler, class Root = NullType> class LinearHierarchy;

    template
    <
        class T1,
        class T2,
        template <class, class> class Handler,
        class Root
    >
    class LinearHierarchy<TypeList<T1, T2>, Handler, Root> : public Handler<T1, LinearHierarchy<T2, Handler, Root> >
    {
    };

    template
    <
        class T,
        template <class, class> class Handler,
        class Root
    >
    class LinearHierarchy<TypeList<T, NullType>, Handler, Root> : public Handler<T, Root>
    {
    };

}


#endif // GENHIERARCHIES_H
