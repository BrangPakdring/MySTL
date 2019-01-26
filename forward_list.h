//
// Created by brang on 1/22/19.
//

#ifndef MYSTL_FORWARD_LIST_H
#define MYSTL_FORWARD_LIST_H

#include "mystl_config.h"
#include "mystl_allocator.h"

BEGIN_NAMESPACE_MYSTD

	struct __forward_list_node_base
	{
		__forward_list_node_base *next;
	};

	template <class T>
	struct __forward_list_node : __forward_list_node_base
	{
		T data;
	};

	inline __forward_list_node_base *
	__forward_make_link(__forward_list_node_base *prev_node, __forward_list_node_base *new_node)
	{
		new_node->next = prev_node->next;
		prev_node->next = new_node;
		return new_node;
	}

	inline size_t __forward_list_size(__forward_list_node_base *node)
	{
		size_t result = 0;
		for (; node; node = node->next)
			++result;
		return result;
	}

	struct __forward_list_iterator_base
	{
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef forward_iterator_tag iterator_category;
		__forward_list_node_base *node;

		__forward_list_iterator_base(__forward_list_node_base *x) : node(x)
		{}

		void incr()
		{
			node = node->next;
		}

		bool operator==(const __forward_list_iterator_base &x) const
		{
			return node == x.node;
		}

		bool operator!=(const __forward_list_iterator_base&x) const
		{
			return node != x.node;
		}
	};

	template <class T, class Ref, class Ptr>
	struct __forward_list_iterator : __forward_list_iterator_base
	{
		typedef __forward_list_iterator<T, Ref, Ptr> self;
		typedef __forward_list_iterator<T, T &, T *> iterator;
		typedef __forward_list_iterator<T, const T &, const T *> const_iterator;
		typedef T value_type;
		typedef Ptr pointer;
		typedef Ref reference;
		typedef __forward_list_node<T> list_node;

		__forward_list_iterator(list_node *x) : __forward_list_iterator_base(x)
		{}

		__forward_list_iterator() : __forward_list_iterator(0)
		{}

		__forward_list_iterator(const iterator &x) : __forward_list_iterator_base(x.node)
		{}

		reference operator*() const
		{
			return ((list_node *) node)->data;
		}

		pointer operator->() const
		{
			return &operator*();
		}

		self &operator++()
		{
			incr();
			return *this;
		}

		const self operator++(int)
		{
			self tmp = *this;
			incr();
			return tmp;
		}
	};

	template <class T, class Alloc = allocator<T>>
	class forward_list
	{
	public:
		typedef T value_type;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef __forward_list_iterator<T, T &, T *> iterator;
		typedef __forward_list_iterator<T, const T &, const T *> const_iterator;

	protected
		typedef __forward_list_node<T> list_node;
		typedef __forward_list_node_base list_node_base;
		typedef __forward_list_iterator_base iterator_base;
		typedef simple_alloc<list_node, allocator<list_node>> list_node_allocator;

		static list_node *create_node(const value_type &x)
		{
			list_node *node = list_node_allocator::allocate();
			try
			{
				construct(&node->data, x);
				node->next = nullptr;
			}
			catch (...)
			{
//				list_node_allocator::allocate(node);
				throw;
			}
			return node;
		}

		static void destroy_node(list_node *node)
		{
			destroy(&node->data);
			list_node_allocator::deallocate(node);
		}

		list_node_base head;
		size_type cnt;
	public:
		forward_list() : cnt(), head()
		{
			head.next = nullptr;
		}

		~forward_list()
		{
			clear();
		}

		iterator before_begin()
		{
			return iterator((list_node*)&head);
		}

		const_iterator cbefore_begin() const
		{
			return const_iterator((list_node*)&head);
		}

		const_iterator before_begin() const
		{
			return cbefore_begin();
		}

		iterator begin()
		{
			return iterator((list_node*)head.next);
		}

		const_iterator cbegin()
		{
			return iterator((list_node*)head.next);
		}

		const_iterator begin() const
		{
			return cbegin();
		}

		iterator end()
		{
			return iterator(nullptr);
		}

		const_iterator cend()
		{
			return iterator(nullptr);
		}

		const_iterator end() const
		{
			return cend();
		}

		size_type size() const
		{
			return /*__forward_list_size(head.next)*/cnt;
		}

		bool empty() const
		{
			return head.next == nullptr;
		}

		void swap(forward_list&l)
		{
			swap(head.next, l.head.next);
		}

		reference front()
		{
			return ((list_node*)head.next)->data;
		}

		const_reference front()const
		{
			return ((list_node*)head.next)->data;
		}

		void push_front(const value_type&x)
		{
			__forward_make_link(&head, create_node(x));
			++cnt;
		}

		void pop_front()
		{
			list_node*node = head.next;
			head.next = node->next;
			destroy_node(node);
			--cnt;
		}

		void clear()
		{
			list_node*cur = (list_node*)head.next;
			while (cur)
			{
				list_node*tmp = cur;
				cur = (list_node*)cur->next;
				destroy_node(tmp);
			}
			head.next = nullptr;
			cnt = 0;
		}

		void insert_after(const_iterator pos, const value_type&value)
		{

		}
	};

END_NAMESPACE_MYSTD

#endif //MYSTL_FORWARD_LIST_H
