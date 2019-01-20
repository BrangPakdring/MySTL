//
// Created by brang on 1/18/19.
//

#ifndef MYSTL_LIST_H
#define MYSTL_LIST_H

#include "mystl_config.h"
#include "mystl_iterator.h"
#include "mystl_allocator.h"
#include "mystl_alloc.h"
#include "mystl_construct.h"

BEGIN_NAMESPACE_MYSTD

	template<class T>
	struct __list_node
	{
		using pointer = __list_node<T> *;
		pointer prev, next;
		T data;
	};

	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		using self = __list_iterator<T, Ref, Ptr>;
		using iterator = __list_iterator<T, T &, T *>;
		using iterator_category = bidirectional_iterator_tag;
		using value_type = T;
		using pointer = Ptr;
		using reference = Ref;
		using difference_type = ptrdiff_t;
		using link_type = __list_node<T> *;
		using size_type = size_t;
		link_type node;

		__list_iterator() = default;

		explicit __list_iterator(link_type x) : node(x)
		{}

		__list_iterator(const iterator &x) : node(x.node)
		{}

		bool operator==(const self &x) const
		{
			return node == x.node;
		}

		bool operator!=(const self &x) const
		{
			return node != x.node;
		}

		reference operator*() const
		{
			return node->data;
		}

		pointer operator->() const
		{
			return &operator*();
		}

		self &operator++()
		{
			node = node->next;
			return *this;
		}

		const self operator++(int)
		{
			self t = *this;
			++*this;
			return t;
		}

		self &operator--()
		{
			node = node->prev;
			return *this;
		}

		const self operator--(int)
		{
			self t = *this;
			--*this;
			return t;
		}
	};

	template<class T, class Alloc = allocator<T>>
	class list
	{
	protected:
		using list_node = __list_node<T>;
		using list_node_allocator = simple_alloc<T, Alloc>;

	public:
		using link_type = list_node *;
		using iterator = __list_iterator<T, T&, T*>;
		using size_type = size_t;
		using reference = T&;
		using difference_type = ptrdiff_t;

	protected:
		link_type node;
		size_type cnt;

		link_type get_node()
		{
			return (link_type)list_node_allocator::allocate();
		}

		void put_node(link_type p)
		{
			list_node_allocator::deallocate(p);
		}

		link_type create_node(const T&x)
		{
			link_type p = get_node();
			construct(&p->data, x);
			return p;
		}

		void destroy_node(link_type p)
		{
			destroy(&p->data);
			put_node(p);
		}

		void empty_initialize()
		{
			node = get_node();
			node->next = node->prev = node;
			cnt = 0;
		}

	DEBUG_PUBLIC(protected):

		void transfer(iterator position, iterator first, iterator last)
		{
			if (position == last)return;
			first.node->prev->next = last.node;
			last.node->prev->next = position.node;
			position.node->prev->next = first.node;
			auto tmp = position.node->prev;
			position.node->prev = last.node->prev;
			last.node->prev = first.node->prev;
			first.node->prev = tmp;
		}

	public:

		list(){empty_initialize();}

		iterator begin()
		{
			return iterator(node->next);
		}

		iterator end()
		{
			return iterator(node);
		}

		bool empty() const
		{
			return node->next == node;
		}

		size_type size() const
		{
			return cnt;
		}

		reference front()
		{
			return *begin();
		}

		reference back()
		{
			return *--end();
		}

		iterator insert(iterator position, const T&x)
		{
			link_type tmp = create_node(x);
			tmp->prev = position.node->prev;
			tmp->next = position.node;
			position.node->prev->next = tmp;
			position.node->prev = tmp;
			++cnt;
			return iterator(tmp);
		}

		void push_front(const T&x)
		{
			insert(begin(), x);
		}

		void push_back(const T&x)
		{
			insert(end(), x);
		}

		iterator erase(iterator position)
		{
			link_type next = position.node->next;
			link_type prev = position.node->prev;
			prev->next = next;
			next->prev = prev;
			destroy_node(position.node);
			--cnt;
			return iterator(next);
		}

		void pop_front()
		{
			erase(begin());
		}

		void pop_back()
		{
			erase(--end());
		}

		void clear()
		{
			link_type cur = node->next;
			while (cur != node)
			{
				link_type tmp = cur;
				cur = cur->next;
				destroy_node(tmp);
			}
			node->prev = node->next = node;
			cnt = 0;
		}

		void remove(const T&value)
		{
			iterator first = begin(), last = end();
			for (iterator it = first; it != last; ++it)
			{
				if (*it == value)erase(it), --cnt;
			}
		}

		void unique()
		{
			iterator first = begin(), last = end(), next = first;
			while (++next != last)
			{
				if (*first == *next)
					erase(first), --cnt;
				first = next;
			}
		}

		void splice(iterator position, list&l)
		{
			if (this != &l && !l.empty())
			{
				transfer(position, l.begin(), l.end());
				difference_type dis = distance(l.begin(), l.end());
				l.cnt -= dis;
				cnt += dis;
			}
		}

		void splice(iterator position, list&l, iterator i)
		{
			iterator j = i; ++j;
			if (position == i || position == j)return;
			transfer(position, i, j);
			--l.cnt;
			++cnt;
		}

		void splice(iterator position, list&l, iterator first, iterator last)
		{
			if (this == &l || first == last)return;
			transfer(position, first, last);
			difference_type dis = distance(first, last);
			l.cnt -= dis;
			cnt += dis;
		}
	};

END_NAMESPACE_MYSTD

#endif //MYSTL_LIST_H
