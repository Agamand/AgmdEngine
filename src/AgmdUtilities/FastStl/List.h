/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#ifndef _LIST_H_
#define _LIST_H_

#include <CommonDefines.h>

#include <Allocator/DefaultAllocator.h>

#include <cstdlib>

namespace AgmdUtilities
{
    template<class T, template<class> class A = DefaultAllocator> class List
    {
    public:
        class ListNode;
        typedef ListNode* ListNodePtr;

	    struct ListNode
	    {
		    ListNode(const T& e) : Next(NULL), Prev(NULL), Element(e) {}

		    ListNodePtr next;
		    ListNodePtr prev;
		    T element;
	    };

        class Iterator
        {
	    public:
		    Iterator() : current(NULL) {}

		    Iterator& operator ++()    { current = current->next; return *this; }
		    Iterator& operator --()    { current = current->prev; return *this; }
		    Iterator  operator ++(a_int32) { Iterator tmp = *this; current = current->next; return tmp; }
		    Iterator  operator --(a_int32) { Iterator tmp = *this; current = current->prev; return tmp; }

		    Iterator& operator +=(a_int32 num)
		    {
			    if(num > 0)
			    {
				    while(num-- && this->current) ++(*this);
			    }
			    else
			    {
				    while(num++ && this->current) --(*this);
			    }
			    return *this;
		    }

		    Iterator  operator + (s32 num) const { Iterator tmp = *this; return tmp += num; }
		    Iterator& operator -=(s32 num) const { return (*this)+=(-num); }
		    Iterator  operator - (s32 num) const { return (*this)+ (-num); }

		    bool operator ==(const Iterator&      other) const { return current == other.current; }
		    bool operator !=(const Iterator&      other) const { return current != other.current; }
		    bool operator ==(const ConstIterator& other) const { return current == other.current; }
		    bool operator !=(const ConstIterator& other) const { return current != other.current; }

		    T & operator * () { return current->Element; }
		    T * operator ->() { return &current->Element; }

	    private:
		    explicit Iterator(ListNodePtr begin) : current(begin) {}

		    ListNodePtr current;

		    friend class List<T>;
		    friend class ConstIterator;
        };

        class ConstIterator
        {
	    public:
		    ConstIterator() : current(NULL) {}

		    ConstIterator& operator ++()    { current = current->next; return *this; }
		    ConstIterator& operator --()    { current = current->prev; return *this; }
		    ConstIterator  operator ++(a_int32) { ConstIterator tmp = *this; current = current->next; return tmp; }
		    ConstIterator  operator --(a_int32) { ConstIterator tmp = *this; current = current->prev; return tmp; }

		    ConstIterator& operator +=(a_int32 num)
		    {
			    if(num > 0)
			    {
				    while(num-- && this->current) ++(*this);
			    }
			    else
			    {
				    while(num++ && this->current) --(*this);
			    }
			    return *this;
		    }

		    ConstIterator  operator + (s32 num) const { ConstIterator tmp = *this; return tmp += num; }
		    ConstIterator& operator -=(s32 num) const { return (*this)+=(-num); }
		    ConstIterator  operator - (s32 num) const { return (*this)+ (-num); }

		    bool operator ==(const ConstIterator&      other) const { return current == other.current; }
		    bool operator !=(const ConstIterator&      other) const { return current != other.current; }
		    bool operator ==(const ConstIterator& other) const { return current == other.current; }
		    bool operator !=(const ConstIterator& other) const { return current != other.current; }

		    T & operator * () { return current->Element; }
		    T * operator ->() { return &current->Element; }

	    private:
		    explicit ConstIterator(ListNodePtr begin) : current(begin) {}

		    ListNodePtr current;

		    friend class List<T>;
		    friend class Iterator;
        };

        List();
        ~List();

        Iterator Begin() const;
        Iterator End() const;

        ConstIterator Begin() const;
        ConstIterator End() const;
        

        /*void push(T, Comparator);*/
        void push_front(T);
        void push_back(T);
        
        void pop(T);
        void pop(Iterator&);
        void pop(ConstIterator&);
        void pop_front();
        void pop_fack();

        a_uint32 size() const;

    private:

        bool            m_bSort;
        ListNodePtr     m_begin;
        ListNodePtr     m_last;
        Allocator       m_allocator;
    };


template <class T, template <class> A> inline List<T,A>::List() :
m_bSort(false), m_size(0),
m_begin(NULL), m_last(NULL)
{}

template <class T, template <class> A> inline List<T,A>::~List()
{
    //Destroy all node;
    ListNodePtr node = m_begin;
    while(node)
    {
        ListNodePtr deleteNode = node;
        node = node->next;
        m_allocator->UnAllocate(node);
    }
    delete m_allocator;
}


template <class T, template <class> A> inline const List<T,A>::ListNode& List<T,A>::Begin()
{
    return *m_begin;
}

template <class T, template <class> A> inline const List<T,A>::ListNode& List<T,A>::End()
{
    return *m_last;
}
        
template <class T, template <class> A> inline void List<T,A>::push_front(T element)
{
    ListNodePtr node = m_allocator->Allocate(1);
    node->next = m_begin;
    m_begin = node;
    !m_last && (m_last = m_begin);
}

template <class T, template <class> A> inline void List<T,A>::push_back(T element)
{
    
    ListNodePtr node = CreateNode(element);
    m_begin = node;
    node->prev = m_last;
    !m_begin && (m_begin = m_last);
}
        
template <class T, template <class> A> inline void List<T,A>::pop(T element)
{
    ListNodePtr node = m_begin;
    while(node)
    {
        if(node->element == element)
        {
            node->prev && (node->prev->next = node->next);
            node->next && (node->next->prev = node->prev);
            m_size--;
            ListNodePtr deleteNode = node;
            m_allocator.UnAllocate(deleteNode);
        }
        node = node->next;

    }
}

template <class T, template <class> A> inline void List<T,A>::pop(Iterator& itr)
{
    if(!itr.current)
        return;

    ListNodePtr node = itr.current;

    node->prev && (node->prev->next = node->next);
    node->next && (node->next->prev = node->prev);
    m_
}

template <class T, template <class> A> inline void List<T,A>::pop(ConstIterator& itr)
{

}

template <class T, template <class> A> inline void List<T,A>::pop_front()
{

}

template <class T, template <class> A> inline void List<T,A>::pop_back()
{

}


template <class T, template <class> A> inline a_uint32 List<T,A>::size() const
{
    return m_size;
}
    #include <FastStl\List.inl>

}
#endif /* _LIST_H_ */
 