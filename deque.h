//
// Created by brang on 1/21/19.
//

#ifndef MYSTL_DEQUE_H
#define MYSTL_DEQUE_H

#include "mystl_config.h"
#include "mystl_allocator.h"
#include "mystl_uninitialized.h"
#include "mystl_algobase.h"

BEGIN_NAMESPACE_MYSTD

	inline size_t __deque_buf_size(size_t n, size_t sz)
	{
		return n ?: sz < 512 ? size_t(512 / sz)
		                    : size_t(1);
	}

	template <class T, class Ref, class Ptr, size_t BufSize>
	struct __deque_iterator
	{
		typedef __deque_iterator<T, T &, T *, BufSize> iterator;
		typedef __deque_iterator<T, const T &, const T *, BufSize> const_iterator;

		static size_t buffer_size()
		{
			return __deque_buf_size(BufSize, sizeof(T));
		}

		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef Ptr pointer;
		typedef Ref reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T **map_pointer;
		typedef __deque_iterator self;

		T *cur;
		T *first;
		T *last;
		map_pointer node;

		void set_node(map_pointer new_node)
		{
			node = new_node;
			first = *new_node;
			last = first + difference_type(buffer_size());
		}

		reference operator*() const
		{
			return *cur;
		}

		pointer operator->() const
		{
			return &operator*();
		}

		difference_type operator-(const self &x) const
		{
			return difference_type(buffer_size()) * (node - x.node - 1) + (cur - first) + (x.last - x.cur);
		}

		self &operator++()
		{
			++cur;
			if (cur == last)
			{
				set_node(node + 1);
				cur = first;
			}
			return *this;
		}

		const self operator++(int)
		{
			self tmp = *this;
			++*this;
			return tmp;
		}

		self &operator--()
		{
			if (cur == first)
			{
				set_node(node - 1);
				cur = last;
			}
			--cur;
			return *this;
		}

		const self operator--(int)
		{
			self tmp = *this;
			--*this;
			return tmp;
		}

		self &operator+=(difference_type n)
		{
			difference_type offset = n + (cur - first);
			difference_type buf_sz = buffer_size();
			if (offset >= 0 && offset < buf_sz)
				cur += n;
			else
			{
				difference_type node_offset =
						offset > 0 ? offset / buf_sz
						           : -difference_type((-offset - 1) / buf_sz) - 1;
				set_node(node + node_offset);
				cur = first + (offset - node_offset * buf_sz);
			}
			return *this;
		}

		self operator+(difference_type n) const
		{
			self tmp = *this;
			return tmp += n;
		}

		self&operator-=(difference_type n)
		{
			return *this += -n;
		}

		self operator-(difference_type n) const
		{
			self tmp = *this;
			return tmp -= n;
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}

		bool operator==(const self&x) const
		{
			return cur == x.cur;
		}

		bool operator!=(const self&x) const
		{
			return !(*this == x);
		}

		bool operator<(const self&x) const
		{
			return node == x.node ? cur < x.cur : node < x.node;
		}
	};

	template <class T, class Alloc = allocator<T>, size_t BufSize = 0>
	class deque
	{
	public:
		typedef T value_type;
		typedef value_type *pointer;
		typedef value_type &reference;
		typedef size_t size_type;
		typedef __deque_iterator<T, T&, T*, BufSize>iterator;
		typedef ptrdiff_t difference_type;

	ACCESSIBILITY(protected):
		typedef pointer *map_pointer;
		typedef simple_alloc<value_type , Alloc>data_allocator;
		typedef simple_alloc<pointer , Alloc>map_allocator;
		using iterator::buffer_size;

		iterator start;
		iterator finish;
		map_pointer map;
		size_type map_size;

		void create_map_and_nodes(size_type num_elements)
		{
			size_type num_nodes = num_elements / buffer_size() + 1;
			map_size = max((size_type)8, num_nodes + 2);
			map = map_allocator::allocate(map_size);
			map_pointer nstart = map + (map_size - num_nodes) / 2;
			map_pointer nfinish = nstart + num_nodes - 1;
			map_pointer cur = nstart;

			try
			{
				do *cur = data_allocator::allocate();
				while (cur++ != nfinish);
			}
			catch (...) // TODO : commit or rollback
			{
				throw;
			}

			start.set_node(nstart);
			finish.set_node(nfinish);
			start.cur = start.first;
			finish.cur = finish.first + num_elements % buffer_size();
		}

		void fill_initialize(size_type n, const value_type& value)
		{
			try
			{
				create_map_and_nodes(n);
				map_pointer cur;
				for (cur = start.node; cur != finish.node; ++cur)
					uninitialized_fill(*cur, *cur + buffer_size(), value);
				uninitialized_fill(finish.first, finish.cur, value);
			}
			catch (...) // TODO : commit or rollback
			{
				throw;
			}
		}

	public:
		deque(size_type n, const value_type&value): start(), finish(), map(), map_size()
		{
			fill_initialize(n, value);
		}

		iterator begin()
		{
			return start;
		}

		iterator end()
		{
			return finish;
		}

		reference operator[](size_type n)
		{
			return start[(difference_type)n];
		}

		reference front()
		{
			return*start;
		}

		reference back()
		{
			iterator tmp = finish;
			--tmp;
			return *tmp;
		}

		size_type size() const
		{
			return size_type(finish - start);
		}

		size_type max_size() const
		{
			return size_type (-1);
		}

		bool empty() const
		{
			return start == finish;
		}


	};

END_NAMESPACE_MYSTD

#endif //MYSTL_DEQUE_H
