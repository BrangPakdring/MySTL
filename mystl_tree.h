//
// Created by brang on 1/26/19.
//

#ifndef MYSTL_TREE_H
#define MYSTL_TREE_H

#include "mystl_config.h"
#include "mystl_iterator.h"
#include "mystl_allocator.h"

BEGIN_NAMESPACE_MYSTD

	enum __rb_tree_color_type
	{
		__rb_tree_red, __rb_tree_black
	};

	struct __rb_tree_node_base
	{
		typedef __rb_tree_color_type color_type;
		typedef __rb_tree_node_base *base_ptr;

		color_type color;
		base_ptr parent, left, right;

		static base_ptr minimum(base_ptr x)
		{
			while (x->left)x = x->left;
			return x;
		}

		static base_ptr maximum(base_ptr x)
		{
			while (x->right)x = x->right;
			return x;
		}
	};

	template <class T>
	struct __rb_tree_node : __rb_tree_node_base
	{
		typedef __rb_tree_node *link_type;
		typedef T value_type;
		value_type value_field;
	};

	struct __rb_tree_base_iterator
	{
		typedef __rb_tree_base_iterator self;
		typedef __rb_tree_node_base::base_ptr base_ptr;
		typedef bidirectional_iterator_tag iterator_category;
		typedef ptrdiff_t difference_type;

		base_ptr node;

		void increment()
		{
			if (node->right)
			{
				node = node->right;
				while (node->left)
					node = node->left;
			}
			else
			{
				base_ptr y = node->parent;
				while (node == y->right)
				{
					node = y;
					y = y->parent;
				}
				if (node->right != y)
					node = y; // ?
			}
		}

		void decrement()
		{
			if (node->color == __rb_tree_red && node->parent->parent == node)
				node = node->right;
			else if (node->left)
			{
				base_ptr y = node->left;
				while (y->right)y = y->right;
				node = y;
			}
			else
			{
				base_ptr y = node->parent;
				while (node == y->left)
				{
					node = y;
					y = y->parent;
				}
				node = y;
			}
		}
	};

	template <class T, class Ref, class Ptr>
	struct __rb_tree_iterator : __rb_tree_base_iterator
	{
		typedef __rb_tree_node<T> *link_type;
		typedef __rb_tree_iterator self;
		typedef __rb_tree_iterator<T, T &, T *> iterator;
		typedef __rb_tree_iterator<T, const T &, const T *> const_iterator;
		typedef NAMESPACE_MYSTD::reverse_iterator<iterator> reverse_iterator;
		typedef NAMESPACE_MYSTD::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef T value_type;
		typedef Ref reference;
		typedef Ptr pointer;

		__rb_tree_iterator() = default;

		explicit __rb_tree_iterator(link_type x) : __rb_tree_base_iterator()
		{
			node = x;
		}

		explicit __rb_tree_iterator(const iterator &i) : __rb_tree_base_iterator()
		{
			node = i.node;
		}

		reference operator*() const
		{
			return link_type(node)->value_field;
		}

		pointer operator->() const
		{
			return &operator*();
		}

		self &operator++()
		{
			increment();
			return *this;
		}

		const self operator++(int)
		{
			self tmp = *this;
			increment();
			return tmp;
		}

		self &operator--()
		{
			decrement();
			return *this;
		}

		const self operator--(int)
		{
			self tmp = *this;
			decrement();
			return tmp;
		}
	};

	template <class Key, class Value, class KeyOfValue, class Compare, class Alloc = allocator<Value>>
	class rb_tree
	{
	protected:
		typedef void *void_pointer;
		typedef __rb_tree_node_base *base_ptr;
		typedef __rb_tree_node<Value> rb_tree_node;
		typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;
		typedef __rb_tree_color_type color_type;
	public:
		typedef Key key_type;
		typedef Value value_type;
		typedef value_type *pointer;
		typedef const value_type *const_pointer;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef rb_tree_node *link_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
	protected:

		link_type get_node()
		{
			return rb_tree_node_allocator::allocate();
		}

		void put_node(link_type p)
		{
			rb_tree_node_allocator::deallocate(p);
		}

		link_type create_node(const value_type &x)
		{
			link_type p = get_node();
			try
			{
				construct(&p, x);
			}
			catch (...)
			{
				put_node(p);
			}
			return p;
		}

		link_type clone_node(link_type x)
		{
			link_type p = create_node(x->value_field);
			p->color = x->color;
			p->left = p->right = nullptr;
			return p;
		}

		size_type cnt;
		link_type header;
		Compare key_compare;

		link_type &root() const
		{
			return header->parent;
		}

		link_type leftmost() const
		{
			return header->left;
		}

		link_type rightmost() const
		{
			return header->right;
		}

		static link_type &left(link_type x)
		{
			return x->left;
		}

		static link_type &right(link_type x)
		{
			return x->right;
		}

		static link_type &parent(link_type x)
		{
			return x->parent;
		}

		static reference value(link_type x)
		{
			return x->value_field;
		}

		static const Key &key(link_type x)
		{
			return KeyOfValue()(value(x));
		}

		static color_type &color(link_type x)
		{
			return x->color;
		}

		static link_type &left(base_ptr x)
		{
			return x->left;
		}

		static link_type &right(base_ptr x)
		{
			return x->right;
		}

		static link_type &parent(base_ptr x)
		{
			return x->parent;
		}

		static reference value(base_ptr x)
		{
			return ((link_type) x)->value_field;
		}

		static const Key &key(base_ptr x)
		{
			return KeyOfValue()(value(x));
		}

		static color_type &color(base_ptr x)
		{
			return x->color;
		}

		static link_type minimum(link_type x)
		{
			return __rb_tree_node_base::minimum(x);
		}

		static link_type maximum(link_type x)
		{
			return __rb_tree_node_base::maximum(x);
		}

	public:
		typedef __rb_tree_iterator<value_type, reference, pointer> iterator;
	private:

		iterator __insert(base_ptr x, base_ptr y, const value_type &v)
		{

		}

		link_type __copy(link_type x, link_type p)
		{

		}

		void __erase(link_type x)
		{

		}

		void init()
		{
			header = get_node();
			color(header) = __rb_tree_red;
			root() = nullptr;
			leftmost() = rightmost() = header;
		}

	public:
		explicit rb_tree(const Compare &comp = Compare()) : cnt(), key_compare(comp)
		{
			init();
		}

		~rb_tree()
		{
			clear();
			put_node(header);
		}

		rb_tree &operator=(const rb_tree &x)
		{

		}

		Compare key_comp() const
		{
			return key_compare;
		}

		iterator begin()
		{
			return leftmost();
		}

		iterator end()
		{
			return header;
		}

		bool empty() const
		{
			return cnt == 0;
		}

		size_type size() const
		{
			return cnt;
		}

		size_type max_size() const
		{
			return size_type(-1);
		}

		void clear()
		{

		}

		pair<iterator, bool> insert_unique(const value_type &v)
		{
			link_type y = header, x = root();
			bool comp = true;
			while (x)
			{
				y = x;
				comp = key_compare(KeyOfValue()(v), key(x));
				x = comp ? left(x) : right(x);
			}
			iterator j = iterator(y);
			if (comp)
			{
				if (j == begin())
					return {__insert(x, y, v), true};
				else --j;
			}
			if (key_compare(key(j.node), KeyOfValue()(v)))
				return {__insert(x, y, v), true};
			return {j, false};
		}

		iterator insert_equal(const value_type &v)
		{
			link_type y = header, x = root();
			while (x)
			{
				y = x;
				x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);
			}
			return __insert(x, y, v);
		}
	};

END_NAMESPACE_MYSTD

#endif //MYSTL_TREE_H
