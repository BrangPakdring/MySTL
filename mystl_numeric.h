//
// Created by brang on 1/29/19.
//

#ifndef MYSTL_NUMERIC_H
#define MYSTL_NUMERIC_H

#include "mystl_config.h"

BEGIN_NAMESPACE_MYSTD

	template <class InputIterator, class T>
	T accumulate(InputIterator first, InputIterator last, T init)
	{
		while (first != last)
			init += *first++;
		return init;
	}

	template <class InputIterator, class T, class BinaryOperation>
	T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation bin_op)
	{
		while (first != last)
			init = bin_op(init, *first++);
		return init;
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result)
	{
		if (first == last)return result;
		*result = *first;
		auto value = *first;
		while (++first != last)
		{
			auto tmp = *first;
			*++result = tmp - value;
			value = tmp;
		}
		return ++result;
	}

	template <class InputIterator, class OutputIterator, class BinaryOperation>
	OutputIterator
	adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation bin_op)
	{
		if (first == last)return result;
		*result = *first;
		auto value = *first;
		while (++first != last)
		{
			auto tmp = *first;
			*++result = bin_op(tmp, value);
			value = tmp;
		}
		return ++result;
	}

	template <class InputIterator1, class InputIterator2, class T>
	T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init)
	{
		while (first1 != last1)
			init += *first1++ * *first2++;
		return init;
	}

	template <class InputIterator1, class InputIterator2, class T, class BinaryOperationMul, class BinaryOperationAdd>
	T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init,
	                BinaryOperationAdd bin_add, BinaryOperationMul bin_mul)
	{
		while (first1 != last1)
			init = bin_add(init, bin_mul(*first1++, *first2++));
		return init;
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result)
	{
		if (first == last)return result;
		*result = *first;
		auto value = *first;
		while (++first != last)
		{
			value += *first;
			*++result = value;
		}
		return ++result;
	}

	template <class InputIterator, class OutputIterator, class BinaryOperation>
	OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation bin_op)
	{
		if (first == last)return result;
		*result = *first;
		auto value = *first;
		while (++first != last)
		{
			value = bin_op(value, *first);
			*++result = value;
		}
		return ++result;
	}

	template <class ForwardIterator, class T>
	void iota(ForwardIterator first, ForwardIterator last, T value)
	{
		while (first != last)
			*first++ = value++;
	}

END_NAMESPACE_MYSTD

#endif //MYSTL_NUMERIC_H
