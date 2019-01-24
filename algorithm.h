//
// Created by brang on 1/21/19.
//

#ifndef MYSTL_ALGORITHM_H
#define MYSTL_ALGORITHM_H

#include "mystl_config.h"
#include <algorithm>

BEGIN_NAMESPACE_MYSTD

	template <class T>
	void swap(T &a, T &b)
	{
		T t = a;
		a = b;
		b =  t;
	}

	// Heap algorithms

	template <class RandomAccessIterator, class Distance, class T>
	inline void __push_heap(RandomAccessIterator first, Distance hole_idx, Distance top_idx, const T&value)
	{
		using difference_type = Distance;
		--first;
		++hole_idx;
		++top_idx;
		difference_type parent = hole_idx / 2;
		while (hole_idx > top_idx && first[parent] < value)
		{
			first[hole_idx] = first[parent];
			hole_idx = parent;
			parent = hole_idx / 2;
		}
		first[hole_idx] = value;
	}

	template <class RandomAccessIterator, class Distance, class T>
	inline void __push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*)
	{
		__push_heap(first, Distance(last - first - 1), Distance(0), T(*(last - 1)));
	}

	template <class RandomAccessIterator>
	inline void push_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		__push_heap_aux(first, last, difference_type(first), value_type(first));
	}

	template <class RandomAccessIterator, class Distance, class T>
	void __adjust_heap(RandomAccessIterator first, Distance hole_idx, Distance len, const T&value)
	{
		--first;
		Distance top_idx = ++hole_idx;
		Distance second_child = hole_idx << 1 | 1;
		while (second_child <= len)
		{
			if (first[second_child] < first[second_child - 1])
				--second_child;

			first[hole_idx] = first[second_child];
			hole_idx = second_child;
			second_child = second_child << 1 | 1;
		}
		if (second_child - 1 == len)
		{
			first[hole_idx] = first[second_child - 1];
			hole_idx = second_child - 1;
		}
		__push_heap(first + 1, hole_idx - 1, top_idx - 1, value);
	}

	template <class RandomAccessIterator, class T, class Distance>
	inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, const T& value, Distance*)
	{
		*result = *first;
		__adjust_heap(first, Distance(0), Distance(last - first), value);
	}

	template <class RandomAccessIterator, class T>
	inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*)
	{
		--last;
		__pop_heap(first, last, last, T(*last), difference_type(first));
	}

	template <class RandomAccessIterator>
	inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		__pop_heap_aux(first, last, value_type(first));
	}

	template <class RandomAccessIterator>
	void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		while (last - first > 1)
			pop_heap(first, last--);
	}

	template <class RandomAccessIterator, class T, class Distance>
	void __make_heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance*)
	{
		if (last - first < 2)return;
		Distance len = last - first;
		Distance parent = len >> 1;
		while (true)
		{
			__adjust_heap(first, parent, len, T(first[parent]));
			if (parent == 0)return;
			--parent;
		}
	}

	template <class RandomAccessIterator>
	inline void make_heap(RandomAccessIterator first, RandomAccessIterator last)
	{
		__make_heap(first, last, value_type(first), difference_type(first));
	}

	// End Heap algorithms

END_NAMESPACE_MYSTD

#endif //MYSTL_ALGORITHM_H
