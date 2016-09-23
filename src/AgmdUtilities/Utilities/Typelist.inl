/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

template <std::size_t N, class List>
struct NthElement
{
    typedef typename NthElement<N - 1, typename List::Tail>::Result Result;
};

template <class List>
struct NthElement<0, List>
{
    typedef typename List::Head Result;
};

template <class List>
struct Size
{
    enum
    {
        Result = Size<typename List::Tail>::Result + 1
    };
};

template <>
struct Size<NullType>
{
    enum
    {
        Result = 0
    };
};

template <class ToFind, class ToCompare, class List>
struct Find_
{
    enum
    {
        Result = Find<ToFind, List>::Result + 1
    };
};

template <class ToFind, class List>
struct Find_<ToFind, ToFind, List>
{
    enum
    {
        Result = 0
    };
};

template <class ToFind, class List>
struct Find
{
    enum
    {
        Result = Find_<ToFind, typename List::Head, typename List::Tail>::Result
    };
};

template <class T, class List>
struct PushBack
{
    typedef TypeList<typename List::Head, typename PushBack<T, typename List::Tail>::Result> Result;
};

template <class T>
struct PushBack<T, NullType>
{
    typedef TypeList<T, NullType> Result;
};

template <class T, class List>
struct PushFront
{
    typedef TypeList<T, List> Result;
};

template <class List1, class List2>
struct Concat
{
    typedef typename Concat<typename PushBack<typename List2::Head, List1>::Result, typename List2::Tail>::Result Result;
};

template <class List1>
struct Concat<List1, NullType>
{
    typedef List1 Result;
};
