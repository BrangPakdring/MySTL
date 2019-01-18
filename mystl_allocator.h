//
// Created by brang on 1/18/19.
//

#ifndef MYSTL_ALLOCATOR_H
#define MYSTL_ALLOCATOR_H

#include "mystl_config.h"

BEGIN_NAMESPACE_MYSTD

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

		pointer allocate(size_type n)
		{
			return 0;
		}

		void deallocate(pointer p)
		{

		}

		pointer address(reference x)
		{
			return (pointer) &x;
		}

		const_pointer const_address(const_reference x)
		{
			return (const_pointer) &x;
		}

		size_type init_page_size()
		{
			return 0;
		}

		size_type max_size() const
		{
			return 0;
		}
	};

END_NAMESPACE_MYSTD

#endif //MYSTL_ALLOCATOR_H
