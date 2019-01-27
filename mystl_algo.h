//
// Created by brang on 1/27/19.
//

#ifndef MYSTL_MYSTL_ALGO_H
#define MYSTL_MYSTL_ALGO_H

#include "mystl_config.h"
#include "iterator.h"

BEGIN_NAMESPACE_MYSTD

	template <class ForwardIterator, class T, class Distance>
	ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T&value, Distance*, forward_iterator_tag)
	{
		Distance len = distance(first, last), half;
		ForwardIterator mid;
		while (len > 0)
		{
			half = len >> 1;
			mid = first;
			advance(mid, first);
			if (*mid < value)
			{
				first = mid;
				++first;
				len = len - half - 1;
			}
			else
				len = half;
		}
		return first;
	}

	template <class RandomAccessIterator, class T, class Distance>
	RandomAccessIterator __lower_bound(RandomAccessIterator first, RandomAccessIterator last, const T&value, Distance*, random_access_iterator_tag)
	{
		Distance len = last - first, half;
		RandomAccessIterator mid;
		while (len > 0)
		{
			half = len >> 1;
			mid = first + half;
			if (*mid < value)
			{
				first = mid + 1;
				len = len - half - 1;
			}
			else
				len = half;
		}
		return first;
	}

	template <class ForwardIterator, class T, class Distance, class Compare>
	ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T&value, const Compare& comp, Distance*, forward_iterator_tag)
	{
		Distance len = distance(first, last), half;
		ForwardIterator mid;
		while (len > 0)
		{
			half = len >> 1;
			mid = first;
			advance(mid, first);
			if (comp(*mid, value))
			{
				first = mid;
				++first;
				len = len - half - 1;
			}
			else
				len = half;
		}
		return first;
	}

	template <class RandomAccessIterator, class T, class Distance, class Compare>
	RandomAccessIterator __lower_bound(RandomAccessIterator first, RandomAccessIterator last, const T&value, const Compare&comp, Distance*, random_access_iterator_tag)
	{
		Distance len = last - first, half;
		RandomAccessIterator mid;
		while (len > 0)
		{
			half = len >> 1;
			mid = first + half;
			if (comp(*mid, value))
			{
				first = mid + 1;
				len = len - half - 1;
			}
			else
				len = half;
		}
		return first;
	}

	template <class ForwardIterator, class T>
	inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T&value)
	{
		return __lower_bound(first, last, value, difference_type(first), iterator_category(first));
	}

	template <class ForwardIterator, class T, class Compare>
	inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T&value, const Compare&comp)
	{
		return __lower_bound(first, last, value, comp, difference_type(first), iterator_category(first));
	}

END_NAMESPACE_MYSTD

#endif //MYSTL_MYSTL_ALGO_H
