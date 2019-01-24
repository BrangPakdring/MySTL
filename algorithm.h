//
// Created by brang on 1/21/19.
//

#ifndef MYSTL_ALGORITHM_H
#define MYSTL_ALGORITHM_H

#include "mystl_config.h"
#include <algorithm>
#include "mystl_heap.h"

BEGIN_NAMESPACE_MYSTD

	template <class T>
	void swap(T &a, T &b)
	{
		T t = a;
		a = b;
		b =  t;
	}

END_NAMESPACE_MYSTD

#endif //MYSTL_ALGORITHM_H
