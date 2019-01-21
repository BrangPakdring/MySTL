//
// Created by brang on 1/21/19.
//

#ifndef MYSTL_ALGORITHM_H
#define MYSTL_ALGORITHM_H

#include "mystl_config.h"
#include <algorithm>

BEGIN_NAMESPACE_MYSTD

	template <class T1, class T2>
	void swap(T1 &a, T2 &b)
	{
		std::swap(a, b);
	}

END_NAMESPACE_MYSTD

#endif //MYSTL_ALGORITHM_H
