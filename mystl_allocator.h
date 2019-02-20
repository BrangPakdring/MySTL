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
	class allocator
	{
	public:
		typedef T value_type;
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef T &reference;
		typedef const T &const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		template <class U>
		struct rebind
		{
			using other = allocator<U>;
		};

		static pointer allocate(size_type n, const void * = nullptr)
		{
			return NAMESPACE_MYSTD::allocate((difference_type) n, (pointer) 0);
		}

		static void deallocate(pointer p, size_type n)
		{
			NAMESPACE_MYSTD::deallocate(p);
		}

		static void construct(pointer p, const T &value)
		{
			NAMESPACE_MYSTD::construct(p, value);
		}

		static void destroy(pointer p)
		{
			NAMESPACE_MYSTD::destroy(p);
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
			return /*1 > tmp ? 1 : */tmp;
		}

		static size_type max_size()
		{
			size_type tmp = UINT_MAX / sizeof(T);
			return /*1 > tmp ? 1 : */tmp;
		}
	};

	template <>
	class allocator<void>
	{
	public:
		typedef void *pointer;
	};

END_NAMESPACE_MYSTD

#endif //MYSTL_ALLOCATOR_H
