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

	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
	struct iterator
	{
		using iterator_category = Category;
		using value_type = T;
		using difference_type = Distance;
		using pointer = Pointer;
		using reference = Reference;
	};

	template<class Iterator>
	struct iterator_traits
	{
		using iterator_category = typename Iterator::iterator_category;
		using value_type = typename Iterator::value_type;
		using difference_type = typename Iterator::difference_type;
		using pointer = typename Iterator::pointer;
		using reference = typename Iterator::reference;
	};

	template<class T>
	struct iterator_traits<T *>
	{
		using iterator_category = random_access_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = T *;
		using reference = T &;
	};

	template<class T>
	struct iterator_traits<const T *>
	{
		using iterator_category = random_access_iterator_tag;
		using value_type = T;
		using difference_type = ptrdiff_t;
		using pointer = const T *;
		using reference = const T &;
	};

	template <class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
	iterator_category(const Iterator&)
	{
		return typename iterator_traits<Iterator>::iterator_category();
	}

	template <class Iterator>
	inline typename iterator_traits<Iterator>::value_type*
	value_type(const Iterator&)
	{
		return static_cast<typename iterator_traits<Iterator>::value_type *>(0);
	}

	template <class Iterator>
	inline typename iterator_traits<Iterator>::difference_type *
	difference_type(const Iterator&)
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
	inline void __advance(InputIterator&i, Distance n, input_iterator_tag)
	{
		while (n--)++i;
	}

	template <class BidirectionalIterator, class Distance>
	inline void __advance(BidirectionalIterator&i, Distance n, bidirectional_iterator_tag)
	{
		if (n >= 0)while (n--)++i;
		else while (n++)--i;
	}

	template <class RandomAccessIterator, class Distance>
	inline void __advance(RandomAccessIterator&i, Distance n, random_access_iterator_tag)
	{
		i += n;
	}

	template <class InputIterator, class Distance>
	inline void advance(InputIterator&i, Distance n)
	{
		__advance(i, n, iterator_category(i));
	}

END_NAMESPACE_MYSTD

#endif //MYSTL_MYSTL_ITERATOR_H
