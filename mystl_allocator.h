//
// Created by brang on 1/18/19.
//

#ifndef MYSTL_ALLOCATOR_H
#define MYSTL_ALLOCATOR_H

#include <new>
#include <climits>
#include "mystl_config.h"
#include "mystl_alloc.h"

BEGIN_NAMESPACE_MYSTD

	template <class T>
	inline T*allocate(ptrdiff_t size, T*)
	{
		T*tmp = (T*)::operator new((size_t)(size * sizeof(T)));
		if (!tmp)
		{
			exit(1);
		}
		return tmp;
	}

	template <class T>
	inline void deallocate(T*buf)
	{
		::operator delete(buf);
	}

	template<class T>
	class allocator
	{
	public:
		using value_type = T;
		using pointer = T *;
		using const_pointer = const T *;
		using reference = T &;
		using const_reference = const T &;
		using size_type = size_t;
		using difference_type = ptrdiff_t ;

		static pointer allocate(size_type n)
		{
			return mystd::allocate((difference_type)n, (pointer)0);
		}

		static void deallocate(pointer p)
		{
			mystd::deallocate(p);
		}

		static pointer address(reference x)
		{
			return (pointer) &x;
		}

		static const_pointer const_address(const_reference x)
		{
			return (const_pointer) &x;
		}

		static size_type init_page_size()
		{
			size_type tmp = 4096 / sizeof(T);
			return 1 > tmp ? 1 : tmp;
		}

		static size_type max_size()
		{
			size_type tmp = UINT_MAX / sizeof(T);
			return 1 > tmp ? 1 : tmp;
		}
	};

	template <>
	class allocator<void>
	{
	public:
		using pointer = void*;
	};

END_NAMESPACE_MYSTD

#endif //MYSTL_ALLOCATOR_H
