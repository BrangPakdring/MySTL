//
// Created by brang on 1/21/19.
//

#ifndef MYSTL_MYSTL_FUNCTION_H
#define MYSTL_MYSTL_FUNCTION_H

#include "mystl_config.h"

BEGIN_NAMESPACE_MYSTD

	// Functor adapters.

	template <class Arg, class Result>
	struct unary_function
	{
		typedef Arg argument_type;
		typedef Result result_type;
	};

	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	// Arithmetic functors.

	template <class T>
	struct plus : binary_function<T, T, T>
	{
		T operator()(const T &x, const T &y) const
		{
			return x + y;
		}
	};

	template <class T>
	struct minus : binary_function<T, T, T>
	{
		T operator()(const T &x, const T &y) const
		{
			return x - y;
		}
	};

	template <class T>
	struct multiplies : binary_function<T, T, T>
	{
		T operator()(const T &x, const T &y) const
		{
			return x * y;
		}
	};

	template <class T>
	struct divides : binary_function<T, T, T>
	{
		T operator()(const T &x, const T &y) const
		{
			return x / y;
		}
	};

	template <class T>
	struct modulus : binary_function<T, T, T>
	{
		T operator()(const T &x, const T &y) const
		{
			return x % y;
		}
	};

	template <class T>
	struct negate : unary_function<T, T>
	{
		T operator()(const T &x) const
		{
			return -x;
		}
	};

	// Relational functors.

	template <class T>
	struct equal_to : binary_function<T, T, bool>
	{
		bool operator()(const T &x, const T &y) const
		{
			return x == y;
		}
	};

	template <class T>
	struct not_equal_to : binary_function<T, T, bool>
	{
		bool operator()(const T &x, const T &y) const
		{
			return x != y;
		}
	};

	template <class T>
	struct less : binary_function<T, T, bool>
	{
		bool operator()(const T &x, const T &y) const
		{
			return x < y;
		}
	};

	template <class T>
	struct less_equal : binary_function<T, T, bool>
	{
		bool operator()(const T &x, const T &y) const
		{
			return x <= y;
		}
	};

	template <class T>
	struct greater : binary_function<T, T, bool>
	{
		bool operator()(const T &x, const T &y) const
		{
			return x > y;
		}
	};

	template <class T>
	struct greater_equal : binary_function<T, T, bool>
	{
		bool operator()(const T &x, const T &y) const
		{
			return x >= y;
		}
	};

	// Logical functors

	template <class T>
	struct logical_and : binary_function<T, T, bool>
	{
		bool operator()(const T &x, const T &y) const
		{
			return x & y;
		}
	};

	template <class T>
	struct logical_or : binary_function<T, T, bool>
	{
		bool operator()(const T &x, const T &y) const
		{
			return x | y;
		}
	};

	template <class T>
	struct logical_not : unary_function<T, bool>
	{
		bool operator()(const T &x) const
		{
			return !x;
		}
	};

END_NAMESPACE_MYSTD

#endif //MYSTL_MYSTL_FUNCTION_H
