//
// Created by brang on 1/21/19.
//

#ifndef MYSTL_ARRAY_H
#define MYSTL_ARRAY_H

#include "mystl_config.h"
#include "mystl_iterator.h"

BEGIN_NAMESPACE_MYSTD

	template <class T, size_t N>
	class array
	{
	ACCESSIBILITY(protected):
		T arr[N];
	public:
		typedef T value_type;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef value_type *iterator;
		typedef const value_type *const_iterator;
		typedef NAMESPACE_MYSTD:: reverse_iterator<iterator>  reverse_iterator;
		typedef NAMESPACE_MYSTD:: reverse_iterator<const_iterator>const_reverse_iterator;

		iterator begin()noexcept
		{
			return arr;
		}

		const_iterator cbegin() const noexcept
		{
			return arr;
		}

		const_iterator begin() const noexcept
		{
			return cbegin();
		}

		reverse_iterator rbegin() noexcept
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator(begin());
		}

		const_reverse_iterator rbegin() const noexcept
		{
			return crbegin();
		}

		iterator end() noexcept
		{
			return arr + N;
		}

		const_iterator cend() const noexcept
		{
			return arr + N;
		}

		const_iterator end()const noexcept
		{
			return cend();
		}

		reverse_iterator rend() noexcept
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator(begin());
		}

		const_reverse_iterator rend() const noexcept
		{
			return crend();
		}

		constexpr bool empty() const noexcept
		{
			return N == 0;
		}

		constexpr size_type size() const noexcept
		{
			return N;
		}

		constexpr size_type max_size() const noexcept
		{
			return N;
		}

		pointer data()
		{
			return arr;
		}

		const_pointer data() const
		{
			return arr;
		}

		reference at(size_type n)
		{
			return operator[](n);
		}

		const_reference at(size_type n) const
		{
			return operator[](n);
		}

		reference front() noexcept
		{
			return *begin();
		}

		const_reference front() const noexcept
		{
			return *begin();
		}

		reference back() noexcept
		{
			return *--end();
		}

		const_reference back() const noexcept
		{
			return *--end();
		}

		reference operator[](size_type n)noexcept
		{
			return arr[n];
		}

		const_reference operator[](size_type n) const noexcept
		{
			return arr[n];
		}
	};

END_NAMESPACE_MYSTD

#endif //MYSTL_ARRAY_H
