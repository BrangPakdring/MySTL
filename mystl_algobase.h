//
// Created by brang on 1/22/19.
//

#ifndef MYSTL_MYSTL_ALGOBASE_H
#define MYSTL_MYSTL_ALGOBASE_H

#include <cstring>
#include "mystl_config.h"
#include "mystl_iterator.h"
#include "type_traits.h"

BEGIN_NAMESPACE_MYSTD

	template <class T>
	inline const T &max(const T &a, const T &b)
	{
		return b < a ? a : b;
	}

	template <class T, class Compare>
	inline const T &max(const T &a, const T &b, Compare comp)
	{
		return comp(a, b) ? b : a;
	}

	template <class T>
	inline const T &min(const T &a, const T &b)
	{
		return a < b ? a : b;
	}

	template <class T, class Compare>
	inline const T &min(const T &a, const T &b, Compare comp)
	{
		return comp(a, b) ? a : b;
	}

	template <class InputIterator1, class InputIterator2>
	inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (!(*first1 == *first2))
				return false;
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate bin_pred)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (!bin_pred(*first1, *first2))
				return false;
		return true;
	}

	template <class ForwardIterator, class T>
	inline void fill(ForwardIterator first, ForwardIterator last, const T &value)
	{
		while (first != last)
			*first++ = value;
	}

	template <class OutputIterator, class Size, class T>
	inline OutputIterator fill_n(OutputIterator first, Size n, const T &value)
	{
		while (n--)
			*first++ = value;
		return first;
	}

	template <class ForwardIterator1, class ForwardIterator2, class T>
	inline void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T *)
	{
		T tmp = *a;
		*a = *b;
		*b = tmp;
	}

	template <class ForwardIterator1, class ForwardIterator2>
	inline void iter_swap(ForwardIterator1 a, ForwardIterator2 b)
	{
		decltype(*a)tmp = *a;
		*a = *b;
		*b = tmp;
//		__iter_swap(a, b, value_type(a));
	}

	template <class InputIterator1, class InputIterator2>
	inline bool
	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
			if (*first1 < *first2)
				return true;
			else if (*first2 < *first1)
				return false;
		return first1 == last1 && first2 != last2;
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	inline bool
	lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
	                        Compare comp)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
			if (comp(*first1, *first2))
				return true;
			else if (comp(*first2, *first1))
				return false;
		return first1 == last1 && first2 != last2;
	}

	inline bool
	lexicographical_compare(const unsigned char *first1, const unsigned char *last1, const unsigned char *first2,
	                        const unsigned char *last2)
	{
		const size_t len1 = last1 - first1;
		const size_t len2 = last2 - first2;
		const int result = memcmp(first1, first2, min(len1, len2));
		return result ? result < 0 : len1 < len2;
	}

	template <class InputIterator1, class InputIterator2>
	inline pair<InputIterator1, InputIterator2>
	mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1 && *first1 == *first2)
			++first1, ++first2;
		return {first1, first2};
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	inline pair<InputIterator1, InputIterator2>
	mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate bin_pred)
	{
		while (first1 != last1 && bin_pred(*first1, *first2))
			++first1, ++first2;
		return {first1, first2};
	}

	template <class T>
	inline void swap(T &a, T &b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	template <class RandomAccessIterator, class OutputIterator, class Difference>
	inline OutputIterator
	__copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, random_access_iterator_tag)
	{
		Difference n = last - first;
		while (n--)
			*result++ = *first++;
		return result;
	}

	template <class T>
	inline T *__copy_t(const T *first, const T *last, T *result, __true_type)
	{
		memmove(result, first, sizeof(T) * (last - first));
		return result + (last - first);
	}

	template <class T>
	inline T *__copy_t(const T *first, const T *last, T *result, __false_type)
	{
		return __copy_d(first, last, result, (ptrdiff_t *) 0);
	}

	template <class InputIterator, class OutputIterator>
	inline OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag)
	{
		while (first != last)
			*result++ = *first++;
		return result;
	}

	template <class RandomAccessIterator, class OutputIterator>
	inline OutputIterator
	__copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, random_access_iterator_tag)
	{
		return __copy_d(first, last, result, difference_type(first));
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator __copy_dispatch(InputIterator first, InputIterator last, OutputIterator result)
	{
		return __copy(first, last, result, iterator_category(first));
	}

	template <class T>
	T *__copy_dispatch(T *first, T *last, T *result)
	{
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		return __copy_t(first, last, result, t());
	}

	template <class T>
	T *__copy_dispatch(const T *first, const T *last, T *result)
	{
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		return __copy_t(first, last, result, t());
	}

	template <class InputIterator, class OutputIterator>
	inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		return __copy_dispatch(first, last, result);
	}

	template <class RandomAccessIterator1, class OutputIterator, class Distance>
	OutputIterator __copy_backward_d(RandomAccessIterator1 first, RandomAccessIterator1 last, OutputIterator result, Distance*)
	{
		Distance n = last - first;
		while (n--)
			*--result = *--last;
		return result;
	}

	template <class BidirectionalIterator1, class BidirectionalIterator2>
	BidirectionalIterator2
	__copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result,
	                random_access_iterator_tag)
	{
		return __copy_backward_d(first, last, result, difference_type(first));
	}

	template <class BidirectionalIterator1, class BidirectionalIterator2>
	BidirectionalIterator2
	__copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result,
	                input_iterator_tag)
	{
		__copy_backward_d(first, last, result, difference_type(first));
	}

	template <class BidirectionalIterator1, class BidirectionalIterator2>
	BidirectionalIterator2
	__copy_backward_dispatch(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result)
	{
		return __copy_backward(first, last, result, iterator_category(first));
	}

	template <class BidirectionalIterator1, class BidirectionalIterator2>
	BidirectionalIterator2
	copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result)
	{
		return __copy_backward_dispatch<BidirectionalIterator1, BidirectionalIterator2>(first, last, result);
	}

END_NAMESPACE_MYSTD

#endif //MYSTL_MYSTL_ALGOBASE_H
