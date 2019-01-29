//
// Created by brang on 1/21/19.
//

#ifndef MYSTL_DEQUE_H
#define MYSTL_DEQUE_H

#include "mystl_config.h"
#include "mystl_allocator.h"
#include "mystl_uninitialized.h"
#include "mystl_algobase.h"
#include <cassert>
BEGIN_NAMESPACE_MYSTD

	inline size_t __deque_buf_size(size_t n, size_t sz)
	{
		size_t r = n ? n : sz < 512 ? size_t(512 / sz)
		                            : size_t(1);
//		cout << r << endl;
		return r;
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

		value_type *cur;
		value_type *first;
		value_type *last;
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

		self &operator-=(difference_type n)
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

		bool operator==(const self &x) const
		{
			return cur == x.cur;
		}

		bool operator!=(const self &x) const
		{
			return !(*this == x);
		}

		bool operator<(const self &x) const
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
		typedef const value_type *const_pointer;
		typedef const value_type &const_reference;
		typedef size_t size_type;
		typedef __deque_iterator<T, T &, T *, BufSize> iterator;
		typedef __deque_iterator<T, const T &, const T *, BufSize> const_iterator;
		typedef NAMESPACE_MYSTD::reverse_iterator<iterator> reverse_iterator;
		typedef NAMESPACE_MYSTD::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t difference_type;

	protected:
		static size_t buffer_size()
		{
			return __deque_iterator<T, T &, T *, BufSize>::buffer_size();
		}

		typedef pointer *map_pointer;
		typedef simple_alloc<pointer, allocator<pointer>> map_allocator;

		iterator start;
		iterator finish;
		map_pointer map;
		size_type map_size;

		pointer allocate_node(size_type n = 1)
		{
			return Alloc::allocate(n * buffer_size());
		}

		void deallocate_node(pointer node, size_type n = 1)
		{
			Alloc::deallocate(node, n * buffer_size());
		}

		void create_map_and_nodes(size_type num_elements)
		{
			size_type num_nodes = num_elements / buffer_size() + 1;
			map_size = max((size_type) 8, num_nodes + 2);
			map = map_allocator::allocate(map_size);
			map_pointer nstart = map + (map_size - num_nodes) / 2;
			map_pointer nfinish = nstart + num_nodes - 1;
			map_pointer cur = nstart;

			try
			{
				for (; cur <= nfinish; ++cur)
					*cur = allocate_node();
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

		void empty_initialize()
		{
			create_map_and_nodes(0);
		}

		void fill_initialize(size_type n, const value_type &value)
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

		void reallocate_map(size_type nodes_to_add, bool add_at_front)
		{
			size_type old_num_nodes = finish.node - start.node + 1;
			size_type new_num_nodes = old_num_nodes + nodes_to_add;
			map_pointer new_nstart;
			if (map_size > 2 * new_num_nodes)
			{
				new_nstart = map + (map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
				if (new_nstart < start.node)
					copy(start.node, finish.node + 1, new_nstart);
				else
					copy_backward(start.node, finish.node + 1, new_nstart + old_num_nodes);
			}
			else
			{
				size_type new_map_size = map_size + max(map_size, nodes_to_add) + 2;
				map_pointer new_map = map_allocator::allocate(new_map_size);
				new_nstart = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
				copy(start.node, finish.node + 1, new_nstart);
				map_allocator::deallocate(map, map_size);
				map = new_map;
				map_size = new_map_size;
			}
			start.set_node(new_nstart);
			finish.set_node(new_nstart + old_num_nodes - 1);
		}

		void reserve_map_at_back(size_type nodes_to_add = 1)
		{
			if (nodes_to_add + 1 > map_size - (finish.node - map))
				reallocate_map(nodes_to_add, false);
		}

		void reserve_map_at_front(size_type nodes_to_add = 1)
		{
			if (nodes_to_add > start.node - map)
				reallocate_map(nodes_to_add, true);
		}

		void push_back_aux(const value_type &t)
		{
			value_type t_copy = t;
			reserve_map_at_back();
			*(finish.node + 1) = allocate_node();

			try
			{
				construct(finish.cur, t_copy);
				finish.set_node(finish.node + 1);
				finish.cur = finish.first;
			}
			catch (...)
			{
				deallocate_node(*(finish.node + 1));
				throw;
			}
		}

		void push_front_aux(const value_type &t)
		{
			value_type t_copy = t;
			reserve_map_at_front();
			*(start.node - 1) = allocate_node();

			try
			{
				start.set_node(start.node - 1);
				start.cur = start.last - 1;
				construct(start.cur, t_copy);
			}
			catch (...)
			{
				start.set_node(start.node + 1);
				start.cur = start.first;
				deallocate_node(*(start.node - 1));
				throw;
			}
		}

		void pop_back_aux()
		{
			deallocate_node(finish.first);
			finish.set_node(finish.node - 1);
			finish.cur = finish.last - 1;
			destroy(finish.cur);
		}

		void pop_front_aux()
		{
			destroy(start.cur);
			deallocate_node(start.first);
			start.set_node(start.node + 1);
			start.cur = start.first;
		}

		iterator insert_aux(iterator pos, const value_type &x)
		{
			difference_type index = pos - start;
			value_type x_copy = x;
			if (index < size() / 2)
			{
				push_front(front());
				iterator front1 = start;
				++front1;
				iterator front2 = front1;
				++front2;
				pos = start + index;
				iterator pos1 = pos;
				++pos1;
				copy(front2, pos1, front1);
			}
			else
			{
				push_back(back());
				iterator back1 = finish;
				--back1;
				iterator back2 = back1;
				--back2;
				pos = start + index;
				copy_backward(pos, back2, back1);
			}
			*pos = x_copy;
			return pos;
		}

	public:

		deque()
		{
			empty_initialize();
		}

		deque(size_type n, const value_type &value) : start(), finish(), map(), map_size()
		{
			fill_initialize(n, value);
		}

		iterator begin()
		{
			return start;
		}

		const_iterator cbegin() const
		{
			return start;
		}

		const_iterator begin() const
		{
			return cbegin();
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		const_reverse_iterator crbegin() const
		{
			return const_reverse_iterator(end());
		}

		const_reverse_iterator rbegin() const
		{
			return crbegin();
		}

		iterator end()
		{
			return finish;
		}

		const_iterator cend() const
		{
			return finish;
		}

		const_iterator end() const
		{
			return cend();
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator crend() const
		{
			return const_reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return crend();
		}

		reference operator[](size_type n)
		{
			return start[(difference_type) n];
		}

		reference front()
		{
			return *start;
		}

		reference back()
		{
			iterator tmp = finish;
			return *--tmp;
		}

		size_type size() const
		{
			return size_type(finish - start);
		}

		size_type max_size() const
		{
			return size_type(-1);
		}

		bool empty() const
		{
			return start == finish;
		}

		void push_back(const value_type &t)
		{
			if (finish.cur < finish.last - 1)
				construct(finish.cur++, t);
			else
				push_back_aux(t);
		}

		void push_front(const value_type &t)
		{
			if (start.cur != start.first)
				construct(--start.cur, t);
			else
				push_front_aux(t);
		}

		void pop_back()
		{
			if (finish.cur != finish.first)
				destroy(--finish.cur);
			else
				pop_back_aux();
		}

		void pop_front()
		{
			if (start.cur != start.last - 1)
				destroy(start.cur++);
			else
				pop_front_aux();
		}

		void clear()
		{
			for (map_pointer node = start.node + 1; node < finish.node; ++node)
			{
				destroy(*node, *node + buffer_size());
				deallocate_node(*node, buffer_size());
			}
			if (start.node != finish.node)
			{
				destroy(start.cur, start.last);
				destroy(finish.first, finish.cur);
				deallocate_node(finish.first, buffer_size());
			}
			else
				destroy(start.cur, finish.cur);
			finish = start;
		}

		iterator erase(iterator pos)
		{
			iterator next = pos;
			++next;
			difference_type index = pos - start;
			if (index < size() / 2)
			{
				copy_backward(start, pos, next);
				pop_front();
			}
			else
			{
				copy(next, finish, pos);
				pop_back();
			}
			return start + index;
		}

		iterator erase(iterator first, iterator last)
		{
			if (first == start && last == finish)
			{
				clear();
				return start;
			}
			else
			{
				difference_type n = last - first;
				difference_type elems_before = first - start;
				if (elems_before < (size() - n) / 2)
				{
					copy_backward(start, first, last);
					iterator new_start = start + n;
					destroy(start, new_start);
					for (map_pointer cur = start.node; cur < new_start.node; ++cur)
						deallocate_node(*cur, buffer_size());
					start = new_start;
				}
				else
				{
					copy(last, finish, first);
					iterator new_finish = finish - n;
					destroy(new_finish, finish);
					for (map_pointer cur = new_finish.node + 1; cur <= finish.node; ++cur)
						deallocate_node(*cur, buffer_size());
					finish = new_finish;
				}
				return start + elems_before;
			}
		}

		iterator insert(iterator position, const value_type &x)
		{
			if (position.cur == start.cur)
			{
				push_front(x);
				return start;
			}
			else if (position.cur == finish.cur)
			{
				push_back(x);
				iterator tmp = finish;
				return --tmp;
			}
			else
				return insert_aux(position, x);
		}
	};

END_NAMESPACE_MYSTD

#endif //MYSTL_DEQUE_H
