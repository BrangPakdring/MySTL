//
// Created by brang on 1/29/19.
//

#ifndef MYSTL_PRED_FUNCTION_H
#define MYSTL_PRED_FUNCTION_H

#include "mystl_config.h"

BEGIN_NAMESPACE_MYSTD

	namespace __my_cxx
	{
		template <class InputIterator1, class InputIterator2 = InputIterator1>
		struct it_equal_to
		{
			bool operator()(const InputIterator1 &i1, const InputIterator2 &i2)
			{
				return *i1 == *i2;
			}
		};

		template <class InputIterator1, class InputIterator2 = InputIterator1>
		struct it_less
		{
			bool operator()(const InputIterator1 &i1, const InputIterator2 &i2)
			{
				return *i1 < *i2;
			}
		};

		template <class InputIterator1, class InputIterator2 = InputIterator1>
		struct it_greater
		{
			bool operator()(const InputIterator1 &i1, const InputIterator2 &i2)
			{
				return *i1 > *i2;
			}
		};
	}

END_NAMESPACE_MYSTD

#endif //MYSTL_PRED_FUNCTION_H
