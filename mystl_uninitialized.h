//
// Created by brang on 1/21/19.
//

#ifndef MYSTL_MYSTL_UNINITIALIZED_H
#define MYSTL_MYSTL_UNINITIALIZED_H

#include "mystl_config.h"
#include "type_traits.h"
#include "mystl_construct.h"
#include "mystl_iterator.h"

BEGIN_NAMESPACE_MYSTD

	template <class ForwardIterator, class Size, class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T &x)
	{
		return __uninitialized_fill_n(first, n, x, value_type(first));
	}

	template <class ForwardIterator, class Size, class T, class T1>
	inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size n, const T &x, T1 *)
	{
		typedef typename __type_traits<T1>::is_POD_type is_POD;
		return __uninitialized_fill_n_aux(first, n, x, is_POD());
	}

	template <class ForwardIterator, class Size, class T>
	inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &x, __true_type)
	{
		return fill_n(first, n, x);
	}

	template <class ForwardIterator, class Size, class T>
	inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T &x, __false_type)
	{
		ForwardIterator cur = first;
		while (n--)
			construct(&*cur++, x);
		return cur;
	}

	template <class InputIterator, class ForwardIterator>
	inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
	{
		return __uninitialized_copy(first, last, result, value_type(result));
	}

	template <class InputIterator, class ForwardIterator, class T>
	inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T*)
	{
		typedef typename __type_traits<T>::is_POD_type is_POD;
		return __uninitialized_copy_aux(first, last, result, is_POD());
	}

	template <class InputIterator, class ForwardIterator, class T>
	inline ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __true_type)
	{
		return copy(first, last, result);
	}

	template <class InputIterator, class ForwardIterator, class T>
	inline ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __false_type)
	{
		ForwardIterator cur = result;
		while (first != last)
			construct(&*cur++, *first++);
		return cur;
	}

	template <class ForwardIterator, class T>
	inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T&x, __false_type)
	{
		fill(first, last, x);
	}

	template <class ForwardIterator, class T>
	inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T&x, __true_type)
	{
		while (first != last)
			construct(&*first++, x);
	}

	template <class ForwardIterator, class T, class T1>
	inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T&x, T1*)
	{
		typedef typename __type_traits<T1>::is_POD_type is_POD;
		__uninitialized_fill_aux(first, last, x, is_POD());
	}

	template <class ForwardIterator, class T>
	inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T&x)
	{
		__uninitialized_fill(first, last, x, value_type(first));
	}

END_NAMESPACE_MYSTD

#endif //MYSTL_MYSTL_UNINITIALIZED_H
