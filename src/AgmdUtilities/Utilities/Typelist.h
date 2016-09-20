/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef TYPELIST_H
#define TYPELIST_H

namespace AgmdUtilities
{
    template <class T1, class T2>
    struct TypeList
    {
        typedef T1 Head;
        typedef T2 Tail;
    };

    struct NullType
    {
    };

#define TYPELIST_1(t1)                                 AgmdUtilities::TypeList<t1, AgmdUtilities::NullType>
#define TYPELIST_2(t1, t2)                             AgmdUtilities::TypeList<t1, TYPELIST_1(t2) >
#define TYPELIST_3(t1, t2, t3)                         AgmdUtilities::TypeList<t1, TYPELIST_2(t2, t3) >
#define TYPELIST_4(t1, t2, t3, t4)                     AgmdUtilities::TypeList<t1, TYPELIST_3(t2, t3, t4) >
#define TYPELIST_5(t1, t2, t3, t4, t5)                 AgmdUtilities::TypeList<t1, TYPELIST_4(t2, t3, t4, t5) >
#define TYPELIST_6(t1, t2, t3, t4, t5, t6)             AgmdUtilities::TypeList<t1, TYPELIST_5(t2, t3, t4, t5, t6) >
#define TYPELIST_7(t1, t2, t3, t4, t5, t6, t7)         AgmdUtilities::TypeList<t1, TYPELIST_6(t2, t3, t4, t5, t6, t7) >
#define TYPELIST_8(t1, t2, t3, t4, t5, t6, t7, t8)     AgmdUtilities::TypeList<t1, TYPELIST_7(t2, t3, t4, t5, t6, t7, t8) >
#define TYPELIST_9(t1, t2, t3, t4, t5, t6, t7, t8, t9) AgmdUtilities::TypeList<t1, TYPELIST_8(t2, t3, t4, t5, t6, t7, t8, t9) >

    template <std::size_t N, class List>
    struct NthElement;

    template <class List>
    struct Size;

    template <class ToFind, class List>
    struct Find;

    template <class T, class List>
    struct PushBack;

    template <class T, class List>
    struct PushFront;

    template <class List1, class List2>
    struct Concat;

#include "Typelist.inl"
}


#endif //TYPELIST_H
