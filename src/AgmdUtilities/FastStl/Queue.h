/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <CommonDefines.h>

namespace AgmdUtilities
{
    template<class T, class Allocator = DefaultAllocator> class Queue
    {
    public:
        class Node;
        typedef Node* NodePtr;
        struct Node
        {
        public:
            bool end();
            T data;
        };
        FastList();
        FastList(bool with_sort, uint32 capacity = 10); //with_sort is used for function Push
        ~FastList();

        const Iterator& Begin() const;
        const Iterator& End() const;
        
        void push(T); // if sort is actived, Push() will sort the element else then Push use Push_Front()
        void push_front(T);
        void push_back(T);
        
        void pop(T);
        void pop(const Iterator&);
        void pop_front();
        void pop_fack();

        void resize(uint32);
        uint32 size() const;

    private:

        NodePtr CreateNode(T element);

        bool            m_bSort;
        NodePtr         m_begin;
        NodePtr         m_last;
        NodePtr         m_begin_garbage;
        uint32          m_size;
        uint32          m_capacity;
        NodePtr         m_storage; //MemPool
    };


template <class T> inline FastList::FastList(uint32 capacity) :
m_bSort(false), m_capacity(capacity), m_size(0), m_storage(new FastList::Iterator[m_capacity]),
m_begin(NULL), m_last(NULL), m_begin_garbage(m_storage)
{
    for(int i = 0; i < m_capacity; i++)
    {
        if(i < m_capacity-1)
            m_storage[i].next = m_begin_garbage[i+1]
        else
            m_storage[i].next = NULL;

        if(i > 0)
            m_storage[i].next = m_begin_garbage[i-1]
        else
            m_storage[i].next = NULL;
    }
}

template <class T> inline FastList::FastList(bool with_sort, uint32 capacity) :
m_bSort(with_sort), m_capacity(capacity), m_size(0), m_storage(new FastList::Iterator[m_capacity]),
m_begin(NULL), m_begin_garbage(m_storage)
{
    for(int i = 0; i < m_capacity; i++)
    {
        if(i < m_capacity-1)
            m_storage[i].next = m_begin_garbage[i+1]
        else
            m_storage[i].next = NULL;

        if(i > 0)
            m_storage[i].next = m_begin_garbage[i-1]
        else
            m_storage[i].next = &s_end;
    }
}

template <class T> inline FastList::~FastList()
{
    delete[] m_storage;
}


template <class T> inline const FastList::Node& FastList::Begin()
{
    return *m_begin;
}

template <class T> inline const FastList::Node& FastList::End()
{
    return *m_last;
}


template <class T> inline const FastList::NodePtr CreateNode(T element)
{
    m_begin_garbage->data = element;
    NodePtr node = m_begin_garbage;
    m_begin_garbage = m_begin_garbage->next;
    m_begin_garbage->prev = NULL;
    return node;
}
        
template <class T> inline void FastList::push(T element)
{
    if(1/*!m_bSort*/) //sort not implemented
    {
        push_front(element);
        return;
    }

    NodePtr node = CreateNode(element);
}

template <class T> inline void FastList::push_front(T element)
{
    NodePtr node = CreateNode(element);
    node->next = m_begin;
    m_begin = node;
    if(!m_last)
        m_last = m_begin;
}

template <class T> inline void FastList::push_back(T element)
{
    
    NodePtr node = CreateNode(element);
    m_begin = node;
    node->prev = m_last;
    if(!m_begin)
        m_begin = m_last;
}
        
template <class T> inline void FastList::pop(T element)
{
}

template <class T> inline void FastList::pop(const Iterator& itr)
{

}

template <class T> inline void FastList::pop_front()
{

}

template <class T> inline void FastList::pop_back()
{

}

template <class T> inline void FastList::resize(uint32 size)
{

}

template <class T> inline uint32 FastList::size() const
{
    return m_size;
}

template <class T> inline uint32 FastList::capacity() const
{
    return m_capacity;
}

#include <FastStl\Queue.inl>

}
#endif /* _QUEUE_H_ */
 