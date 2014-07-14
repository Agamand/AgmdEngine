/*
============================================================================
AgmdUtilities - Utilities Lib
Author : Cyril Basset (basset.cyril@gmail.com - https://github.com/Agamand)
https://github.com/Agamand/AgmdEngine
============================================================================
*/

#define USE_STL_VECTOR
#ifdef USE_STL_VECTOR
	#include <vector>
	#define a_vector std::vector
#else
	#ifndef _VECTOR_H_
	#define _VECTOR_H_

	#include <CommonDefines.h>

	#define DEFAULT_CAPACITY 10

	#include <Allocator/DefaultAllocator.h>

	namespace AgmdUtilities
	{
		template<typename T, template <typename> class A = DefaultAllocator>
		class Vector
		{
		public:
			Vector();
			Vector(a_uint32 size);
			Vector(a_uint32 size,T val);
			Vector(Vector& other );
			~Vector();

			void push_back(T);
			void pop_back();
			void clear();

			bool empty()

			void resize(a_uint32 size);
			void resize(a_uint32 size,const T val);
			a_uint32 size() const;
			a_uint32 capacity() const;


			T& operator[](a_uint32 i);
			const T& operator[](a_uint32 i) const;

		private:
			void resize_capacity(a_uint32 capacity);


			a_uint32        m_size;
			a_uint32        m_capacity;
			T*              m_storage;
			Allocator<T>*   m_allocator;
		};

		#include "Vector.inl"
		
	}
	#define a_vector AgmdUtilities::Vector
	

	#endif /* _VECTOR_H_ */
	
	
#endif 
