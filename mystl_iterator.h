//
// Created by brang on 1/18/19.
//

#ifndef MYSTL_MYSTL_ITERATOR_H
#define MYSTL_MYSTL_ITERATOR_H

#include "mystl_config.h"

BEGIN_NAMESPACE_MYSTD

	struct input_iterator_tag
	{
	};
	struct output_iterator_tag
	{
	};
	struct forward_iterator_tag : input_iterator_tag
	{
	};
	struct bidirectional_iterator_tag : forward_iterator_tag
	{
	};
	struct random_access_iterator_tag : bidirectional_iterator_tag
	{
	};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
	struct iterator
	{
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	template <class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
	};

	template <class T>
	struct iterator_traits<T *>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T *pointer;
		typedef T &reference;
	};

	template <class T>
	struct iterator_traits<const T *>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef const T *pointer;
		typedef const T &reference;
	};

	template <class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
	iterator_category(const Iterator &)
	{
		return typename iterator_traits<Iterator>::iterator_category();
	}

	template <class Iterator>
	inline typename iterator_traits<Iterator>::value_type *
	value_type(const Iterator &)
	{
		return static_cast<typename iterator_traits<Iterator>::value_type *>(0);
	}

	template <class Iterator>
	inline typename iterator_traits<Iterator>::difference_type *
	difference_type(const Iterator &)
	{
		return static_cast<typename iterator_traits<Iterator>::difference_type *>(0);
	}

	template <class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
	__distance(InputIterator first, InputIterator last, input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first != last)++first, ++n;
		return n;
	}

	template <class RandomAccessIterator>
	inline typename iterator_traits<RandomAccessIterator>::difference_type
	__distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
	{
		return last - first;
	}

	template <class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		return __distance(first, last, typename iterator_traits<InputIterator>::iterator_category());
	}

	template <class InputIterator, class Distance>
	inline void __advance(InputIterator &i, Distance n, input_iterator_tag)
	{
		while (n--)++i;
	}

	template <class BidirectionalIterator, class Distance>
	inline void __advance(BidirectionalIterator &i, Distance n, bidirectional_iterator_tag)
	{
		if (n >= 0)while (n--)++i;
		else while (n++)--i;
	}

	template <class RandomAccessIterator, class Distance>
	inline void __advance(RandomAccessIterator &i, Distance n, random_access_iterator_tag)
	{
		i += n;
	}

	template <class InputIterator, class Distance>
	inline void advance(InputIterator &i, Distance n)
	{
		__advance(i, n, iterator_category(i));
	}

	template <class Iterator>
	struct reverse_iterator
	{
	protected:
		Iterator current;
	public:
		typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
		typedef typename iterator_traits<Iterator>::value_type value_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::pointer pointer;
		typedef typename iterator_traits<Iterator>::reference reference;
		typedef Iterator iterator_type;
		typedef reverse_iterator<Iterator> self;
		reverse_iterator() = default;

		explicit reverse_iterator(iterator_type x) : current(x)
				{}

		bool operator==(const self&x)const
		{
			return current == x.current;
		}

		bool operator!=(const self&x)const
		{
			return current != x.current;
		}

		iterator_type base() const
		{
			return current;
		}

		reference operator*() const
		{
			Iterator tmp = current;
			return *--tmp;
		}

		pointer operator->() const
		{
			return &operator*();
		}

		self &operator++()
		{
			--this->current;
			return *this;
		}

		const self operator++(int)
		{
			self tmp = *this;
			--this->current;
			return tmp;
		}

		self &operator--()
		{
			++this->current;
			return *this;
		}

		const self operator--(int)
		{
			self tmp = *this;
			++this->current;
			return tmp;
		}
	};

END_NAMESPACE_MYSTD

#endif //MYSTL_MYSTL_ITERATOR_H
