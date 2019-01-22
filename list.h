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
#include "algorithm.h"

BEGIN_NAMESPACE_MYSTD

	template <class T>
	struct __list_node
	{
		typedef __list_node<T> *pointer;
		pointer prev, next;
		T data;
	};

	template <class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef __list_iterator<T, Ref, Ptr> self;
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*>const_iterator;
		typedef bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef Ptr pointer;
		typedef Ref reference;
		typedef ptrdiff_t difference_type;
		typedef __list_node<T> *link_type;
		typedef size_t size_type;
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
			node = node->next;
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
			node = node->prev;
			return t;
		}
	};

	template <class T, class Alloc = allocator<T>>
	class list
	{
	ACCESSIBILITY(protected):
		typedef __list_node<T> list_node;
		typedef simple_alloc<T, Alloc> list_node_allocator;

	public:
		typedef list_node *link_type;
		typedef typename __list_iterator<T, T&, T*>::iterator iterator;
		typedef typename iterator::const_iterator const_iterator;
		typedef NAMESPACE_MYSTD::reverse_iterator<iterator> reverse_iterator;
		typedef NAMESPACE_MYSTD::reverse_iterator<const_iterator>const_reverse_iterator;
		typedef size_t size_type;
		typedef T value_type;
		typedef T &reference;
		typedef ptrdiff_t difference_type;

	ACCESSIBILITY(protected):
		link_type node;
		size_type cnt;

		link_type get_node()
		{
			return (link_type) list_node_allocator::allocate();
		}

		void put_node(link_type p)
		{
			list_node_allocator::deallocate((T *) p);
		}

		link_type create_node(const T &x)
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

		list()
		{
			empty_initialize();
		}

		list(const list &x)
		{
			// TODO
		}

		list(list&&x) noexcept
		{
			node = x.node;
			cnt = x.cnt;
		}

		list(const initializer_list<value_type>&il) :list()
		{
			for (const auto&item : il)
				push_back(item);
		}

		~list()
		{
			this->clear();
		}

		iterator begin()
		{
			return iterator(node->next);
		}

		const_iterator cbegin() const
		{
			return const_iterator(node->next);
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
			return iterator(node);
		}

		const_iterator cend() const
		{
			return const_iterator(node);
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

		iterator insert(iterator position, const T &x)
		{
			link_type tmp = create_node(x);
			tmp->prev = position.node->prev;
			tmp->next = position.node;
			position.node->prev->next = tmp;
			position.node->prev = tmp;
			++cnt;
			return iterator(tmp);
		}

		void push_front(const T &x)
		{
			insert(begin(), x);
		}

		void push_back(const T &x)
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

		void remove(const T &value)
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

		/**
		 * Splice list @e x before @e position.
		 * @param position The position where to splice a list before.
		 * @param x The list to splice into @e position.
		 */
		void splice(iterator position, list &x)
		{
			if (this != &x && !x.empty())
			{
				transfer(position, x.begin(), x.end());
				difference_type dis = distance(x.begin(), x.end());
				x.cnt -= dis;
				cnt += dis;
			}
		}

		/**
		 * Splice iterator @e i in list @e x into @e position.
		 * @param position The position where to splice an element before.
		 * @param x The list where iterator @e i was in.
		 * @param i The iterator to splice into @e position.
		 */
		void splice(iterator position, list &x, iterator i)
		{
			iterator j = i;
			++j;
			if (position == i || position == j)return;
			transfer(position, i, j);
			--x.cnt;
			++cnt;
		}

		/**
		 * Splice elements between iterators @e first and @e last into @e position ranged from
		 * [first, last).
		 * @param position The position where to splice elements before.
		 * @param x The list where iterators @e first and @e last was in.
		 * @param first The first iterator.
		 * @param last The last iterator.
		 */
		void splice(iterator position, list &x, iterator first, iterator last)
		{
			if (this == &x || first == last)return;
			transfer(position, first, last);
			difference_type dis = distance(first, last);
			x.cnt -= dis;
			cnt += dis;
		}

		void reverse()
		{
			if (cnt < 2)return;
			iterator first = ++begin(), last = end();
			while (first != last)
			{
				iterator old = first++;
				transfer(begin(), old, first);
			}
		}

		/**
		 * Merge current list with another list @e x, it must be guaranteed that
		 * before the method call both lists are sorted using operator<.
		 * @param x The list to sort with current one.
		 */
		void merge(list &x)
		{
			iterator first1 = begin(), last1 = end(), first2 = x.begin(), last2 = x.end();
			while (first1 != last1 && first2 != last2)
			{
				if (*first2 < *first1)
				{
					iterator next = first2;
					transfer(first1, first2, ++next);
					first2 = next;
				}
				else
					++first1;
			}
			if (first2 != last2)
				transfer(last1, first2, last2);
		}

		/**
		 * Merge current list with another list @e x, it must be guaranteed that
		 * before the method call both lists are sorted using strict weak ordering
		 * comparer @e comp.
		 * @param x The list to sort with current one.
		 */
		template <class StrictWeakOrdering>
		void merge(list &x, StrictWeakOrdering comp)
		{
			iterator first1 = begin(), last1 = end(), first2 = x.begin(), last2 = x.end();
			while (first1 != last1 && first2 != last2)
			{
				if (comp(*first2, *first1))
				{
					iterator next = first2;
					transfer(first1, first2, ++next);
					first2 = next;
				}
				else
					++first1;
			}
			if (first2 != last2)
				transfer(last1, first2, last2);
		}

		void swap(list &x)
		{
			mystd::swap(node, x.node);
			mystd::swap(cnt, x.cnt);
		}

//		void print(const char*s = "")
//		{
//			puts(s);
//			for (auto i : *this)
//				printf("%d\t", i);
//			puts("");
//		}

		/**
		 * Sort current list using merge sort according to operator<.
		 */
		void sort()
		{
			if (size() < 2)return;
			list carry, counter[64];
			int fill = 0;
			while (!empty())
			{
//				this->print("this origin");
//				carry.print("carry origin");
				carry.splice(carry.begin(), *this, begin());
//				this->print("this here");
//				carry.print("carry here");
				int i = 0;
//				char buf[200];
				while (i < fill && !counter[i].empty())
				{
//					carry.print("carry o");
//					sprintf(buf, "counter[%d] o", i);
//					counter[i].print(buf);
					carry.merge(counter[i]);
//					carry.print("carry h");
//					sprintf(buf, "counter[%d] o", i);
//					counter[i].print(buf);
					++i;
				}
				carry.swap(counter[i]);
//				carry.print("carry hh");
//				sprintf(buf, "counter[%d] hh", i);
//				counter[i].print(buf);
				if (i == fill)++fill;
			}
			for (int i = 1; i < fill; ++i)
				counter[i].merge(counter[i - 1]);
			swap(counter[fill - 1]);
		}

		/**
		 * Sort current list using merge sort according to strict weak ordering
		 * comparer @e comp.
		 */
		template <class StrictWeakOrdering>
		void sort(StrictWeakOrdering comp)
		{
			if (size() < 2)return;
			list carry, counter[64];
			int fill = 0;
			while (!empty())
			{
				carry.splice(carry.begin(), *this, begin());
				int i = 0;
				while (i < fill && !counter[i].empty())
				{
					counter[i].merge(carry, comp);
					carry.swap(counter[i++]);
				}
				carry.swap(counter[i]);
				if (i == fill)++fill;
			}
			for (int i = 1; i < fill; ++i)
				counter[i].merge(counter[i - 1], comp);
			swap(counter[fill - 1]);
		}

		inline bool operator==(const list&x) const
		{
			iterator first1 = begin(), last1 = end(), first2 = x.begin(), last2 = x.end();
			for (; first1 != last1 && first2 != last2; ++first1, ++first2)
			{
				if (*first1 != *first2)return false;
			}
			return first1 == last1 && first2 == last2;
		}

		inline bool operator!=(const list&x) const
		{
			return !operator==(x);
		}
	};

END_NAMESPACE_MYSTD

#endif //MYSTL_LIST_H
