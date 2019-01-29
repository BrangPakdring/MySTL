//
// Created by brang on 1/27/19.
//

#ifndef MYSTL_MYSTL_ALGO_H
#define MYSTL_MYSTL_ALGO_H

#include "mystl_config.h"
#include "iterator.h"
#include "_pred_function.h"

BEGIN_NAMESPACE_MYSTD

	template <class ForwardIterator, class T, class Distance>
	ForwardIterator
	__lower_bound(ForwardIterator first, ForwardIterator last, const T &value, Distance *, forward_iterator_tag)
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
	RandomAccessIterator
	__lower_bound(RandomAccessIterator first, RandomAccessIterator last, const T &value, Distance *,
	              random_access_iterator_tag)
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
	ForwardIterator
	__lower_bound(ForwardIterator first, ForwardIterator last, const T &value, const Compare &comp, Distance *,
	              forward_iterator_tag)
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
	RandomAccessIterator
	__lower_bound(RandomAccessIterator first, RandomAccessIterator last, const T &value, const Compare &comp,
	              Distance *, random_access_iterator_tag)
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

	template <class ForwardIterator, class T, class Compare>
	inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T &value, const Compare &comp)
	{
		return __lower_bound(first, last, value, comp, difference_type(first), iterator_category(first));
	}

	template <class ForwardIterator, class T>
	inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T &value)
	{
		return __lower_bound(first, last, value, less<typename iterator_traits<ForwardIterator>::value_type>(),
		                     difference_type(first), iterator_category(first));
	}

	template <class ForwardIterator>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
	{
		if (first == last)return last;
		ForwardIterator next = first;
		while (++next != last)
		{
			if (*first == *next)return first;
			first = next;
		}
		return last;
	}

	template <class ForwardIterator, class BinaryPredicate>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate bin_pred)
	{
		if (first == last)return last;
		ForwardIterator next = first;
		while (++next != last)
		{
			if (bin_pred(*first, *next))return first;
			first = next;
		}
		return last;
	}

	template <class InputIterator, class T>
	typename InputIterator::difference_type count(InputIterator first, InputIterator last, const T &value)
	{
		typename InputIterator::difference_type n = 0;
		while (first != last)
			if (*first++ == value)
				++n;
		return n;
	}

	template <class InputIterator, class Predicate>
	typename InputIterator::difference_type count_if(InputIterator first, InputIterator last, Predicate pred)
	{
		typename InputIterator::difference_type n = 0;
		while (first != last)
			if (pred(*first++))
				++n;
		return n;
	}

	template <class InputIterator, class Predicate>
	InputIterator find_if(InputIterator first, InputIterator last, Predicate pred)
	{
		while (first != last && !pred(*first))++first;
		return first;
	}

	template <class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, const T &value)
	{
		while (first != last && *first != value)
			++first;
		return first;
	}

	template <class ForwardIterator1, class ForwardIterator2>
	inline ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
	                                 ForwardIterator2 first2, ForwardIterator2 last2)
	{
		// TODO
	}

	template <class InputIterator, class ForwardIterator>
	InputIterator find_first_of(InputIterator first1, InputIterator last1,
	                            ForwardIterator first2, ForwardIterator last2)
	{
		for (; first1 != last1; ++first1)
			for (auto it = first2; it != last2; ++it)
				if (*first1 == *it)
					return first1;
		return last1;
	}

	template <class InputIterator, class ForwardIterator, class BinaryPredicate>
	InputIterator find_first_of(InputIterator first1, InputIterator last1,
	                            ForwardIterator first2, ForwardIterator last2,
	                            BinaryPredicate bin_pred)
	{
		for (; first1 != last1; ++first1)
			for (auto it = first2; it != last2; ++it)
				if (bin_pred(*first1, *it))
					return first1;
		return last1;
	}

	template <class InputIterator, class Function>
	Function for_each(InputIterator first, InputIterator last, Function f)
	{
		while (first != last)
			f(*first++);
		return f;
	}

	template <class ForwardIterator, class Generator>
	void generate(ForwardIterator first, ForwardIterator last, Generator gen)
	{
		while (first != last)
			*first++ = gen();
	}

	template <class OutputIterator, class Size, class Generator>
	OutputIterator generate_n(OutputIterator first, Size n, Generator gen)
	{
		while (n--)*first++ = gen();
		return first;
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
	              const Compare &comp)
	{
		while (first1 != last1 && first2 != last2)
			if (comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				++first1;
			else
				++first1, ++first2;
		return first2 == last2;
	}

	template <class InputIterator1, class InputIterator2>
	bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		return includes(first1, first2, last1, last2, less<typename iterator_traits<InputIterator1>::value_type>());
	}

	template <class ForwardIterator, class Compare>
	ForwardIterator max_element(ForwardIterator first, ForwardIterator last, const Compare &comp)
	{
		if (first == last)return first;
		ForwardIterator result = first;
		while (++first != last)
			if (comp(*result, *first))
				result = first;
		return result;
	}

	template <class ForwardIterator>
	ForwardIterator max_element(ForwardIterator first, ForwardIterator last)
	{
		return max_element(first, last, less<typename iterator_traits<ForwardIterator>::value_type>());
	}

	template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
	OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
	                     OutputIterator result, const Compare &comp)
	{
		while (first1 != last1 && first2 != last2)
			if (comp(*first1, *first2))
				*result++ = *first1++;
			else
				*result++ = *first2++;
		return copy(first2, last2, copy(first1, last1, result));
	}

	template <class InputIterator1, class InputIterator2, class OutputIterator>
	OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
	                     OutputIterator result)
	{
		return merge(first1, last1, first2, last2, result,
		             less<typename iterator_traits<InputIterator1>::value_type>());
	}

	template <class ForwardIterator, class Compare>
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last, const Compare &comp)
	{
		if (first == last)return first;
		ForwardIterator result = first;
		while (++first != last)
			if (comp(*first, *result))
				result = first;
		return result;
	}

	template <class ForwardIterator>
	ForwardIterator min_element(ForwardIterator first, ForwardIterator last)
	{
		return min_element(first, last, less<typename iterator_traits<ForwardIterator>::value_type>());
	}

	template <class BidirectionalIterator, class Predicate>
	BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred)
	{
		// TODO
	}

	template <class ForwardIterator, class OutputIterator, class Predicate>
	ForwardIterator remove_copy_if(ForwardIterator first, ForwardIterator last, OutputIterator result, Predicate pred)
	{
		while (first != last)
		{
			if (!pred(*first))
				*result++ = *first;
			++first;
		}
		return result;
	}

	template <class ForwardIterator, class Predicate>
	ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred)
	{
		first = find_if(first, last, pred);
		ForwardIterator next = first;
		return first == last ? first : remove_copy_if(++next, last, first, pred);
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T &value)
	{
		using T = typename iterator_traits<InputIterator>::value_type;
		return remove_copy_if(first, last, result, [&value](const T &v)
		{ return v == value; });
		while (first != last)
		{
			if (*first != value)
				*result++ = *first;
			++first;
		}
		return result;
	}

	template <class ForwardIterator, class T>
	ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T &value)
	{
		return remove_if(first, last, [&value](const T &v)
		{ return v == value; });
		first = find(first, last, value);
		ForwardIterator next = first;
		return first == last ? first : remove_copy(++next, last, first, value);
	}

	template <class InputIterator, class Predicate, class T>
	void replace_if(InputIterator first, InputIterator last, Predicate pred, const T &value)
	{
		while (first != last)
		{
			if (pred(*first))
				*first = value;
			++first;
		}
	}

	template <class InputIterator, class T>
	void replace(InputIterator first, InputIterator last, const T &value)
	{
		replace_if(first, last, [&value](const T &v)
		{ return v == value; }, value);
	}

	template <class InputIterator, class OutputIterator, class Predicate, class T>
	OutputIterator
	replace_copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate pred, const T &value)
	{
		for (; first != last; ++first, ++result)
			*result = pred(*first) ? value : *first;
		return result;
	}

	template <class InputIterator, class OutputIterator, class T>
	OutputIterator
	replace_copy(InputIterator first, InputIterator last, OutputIterator result, const T&old_value, const T &new_value)
	{
		return replace_copy_if(first, last, result, [&old_value](const T&v){ return v == old_value;}, new_value);
	}



END_NAMESPACE_MYSTD

#endif //MYSTL_MYSTL_ALGO_H
