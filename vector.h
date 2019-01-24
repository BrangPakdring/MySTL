//
// Created by brang on 1/18/19.
//

#include "mystl_config.h"
#include "mystl_allocator.h"
#include "mystl_algobase.h"
#include "mystl_uninitialized.h"

#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

BEGIN_NAMESPACE_MYSTD

	template <class T, class Alloc = allocator<T>>
	class vector
	{
	public:
		typedef T value_type;
		typedef value_type *pointer;
		typedef value_type &reference;
		typedef value_type *iterator;
		typedef const value_type *const_iterator;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef NAMESPACE_MYSTD::reverse_iterator<iterator> reverse_iterator;
		typedef NAMESPACE_MYSTD::reverse_iterator<const_iterator> const_reverse_iterator;

	ACCESSIBILITY(protected):

		typedef simple_alloc<value_type, Alloc> data_allocator;
		iterator start;
		iterator finish;
		iterator end_of_storage;

		void insert_aux(iterator position, const value_type &x)
		{
			if (finish != end_of_storage)
			{
				construct(finish, *(finish - 1));
				++finish;
				copy_backward(position, finish - 2, finish - 1);
				*position = x;
			}
			else
			{
				const size_type old_size = size();
				const size_type len = old_size ? old_size << 1 : 1;
				iterator new_start = data_allocator::allocate(len);
				iterator new_finish = new_start;
				try
				{
					new_finish = uninitialized_copy(start, position, new_start);
					construct(new_finish, x);
					++new_finish;
					new_finish = uninitialized_copy(position, finish, new_finish);
				}
				catch (...) // TODO: commit or rollback
				{
					destroy(new_start, new_finish);
					data_allocator::deallocate(new_start, len);
					throw;
				}
				destroy(start, finish);
				deallocate();
				start = new_start;
				finish = new_finish;
				end_of_storage = start + len;
			}
		}

		void deallocate()
		{
			if (start)
				data_allocator::deallocate(start, end_of_storage - start);
		}

		void fill_initialize(size_type n, const value_type &value)
		{
			start = allocate_and_fill(n, value);
			finish = start + n;
			end_of_storage = finish;
		}

		iterator allocate_and_fill(size_type n, const value_type &x)
		{
			iterator result = data_allocator::allocate(n);
			value_type x_copy = x;
			uninitialized_fill_n(result, n, x_copy);
			return result;
		}

	public:
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

		size_type size() const
		{
			return size_type(end() - begin());
		}

		size_type capacity() const
		{
			return size_type(end_of_storage - start);
		}

		bool empty() const
		{
			return start == finish;
		}

		reference operator[](size_type n)
		{
			return start[n];
		}

		vector() : start(), finish(), end_of_storage()
		{
		}

		vector(const initializer_list<value_type>&il) : vector()
		{
			for (const auto&item : il)
				push_back(item);
		}

		vector(size_type n, const value_type &value) : vector()
		{
			fill_initialize(n, value);
		}

		explicit vector(size_type n) : vector()
		{
			fill_initialize(n, value_type());
		}

		template <class Iterator>
		vector(Iterator first, Iterator last): vector()
		{
			while (first != last)
				push_back(*first++);
		}

		~vector()
		{
			destroy(start, finish);
		}

		reference front()
		{
			return *begin();
		}

		reference back()
		{
			return *(end() - 1);
		}

		void push_back(const value_type &x)
		{
			if (finish != end_of_storage)
				construct(finish++, x);
			else
				insert_aux(end(), x);
		}

		void pop_back()
		{
			destroy(--finish);
		}

		iterator erase(iterator position)
		{
			if (position + 1 != finish)
				copy(position + 1, finish, position);
			destroy(--finish);
			return position;
		}

		void resize(size_type new_size, const value_type &x)
		{
			if (new_size < size())
				erase(start + new_size, finish);
			else
				insert(end(), new_size - size(), x);
		}

		void resize(size_type new_size)
		{
			resize(new_size, value_type());
		}

		void clear()
		{
			erase(start, finish);
		}

		void insert(iterator position, size_type n, const value_type& x)
		{
			if (!n)return;
			if (size_type(end_of_storage - finish) >= n)
			{
				value_type x_copy = x;
				const size_type elems_after = finish - position;
				iterator old_finish = finish;
				if (elems_after > n)
				{
					uninitialized_copy(finish - n, finish, finish);
					finish += n;
					copy_backward(position, old_finish - n, old_finish);
					fill(position, position + n, x_copy);
				}
				else
				{
					uninitialized_fill_n(finish, n - elems_after, x_copy);
					finish += n - elems_after;
					uninitialized_copy(position, old_finish, finish);
					finish += elems_after;
					fill(position, old_finish, x_copy);
				}
			}
			else
			{
				const size_type old_size = size();
				const size_type len = old_size + max(old_size, n);
				iterator new_start = data_allocator::allocate(len);
				iterator new_finish = new_start;
				try
				{
					new_finish = uninitialized_copy(start, position, new_start);
					new_finish = uninitialized_fill_n(new_finish, n, x);
					new_finish = uninitialized_copy(position, finish, new_finish);
				}
				catch (...) // TODO: commit or rollback
				{
					destroy(new_start, new_finish);
					data_allocator::deallocate(new_start, len);
					throw;
				}
				destroy(start, finish);
				deallocate();
				start = new_start;
				finish = new_finish;
				end_of_storage = start + len;
			}
		}

		void insert(iterator position, const value_type& x)
		{
			insert(position, 1, x);
		}
	};

END_NAMESPACE_MYSTD

#endif //MYSTL_VECTOR_H
