//
// Created by brang on 1/22/19.
//

#ifndef MYSTL_MYSTL_ALGOBASE_H
#define MYSTL_MYSTL_ALGOBASE_H

#include "mystl_config.h"

BEGIN_NAMESPACE_MYSTD

	template <class T>
	T&max(const T&a, const T&b)
	{
		return b < a ? a : b;
	}

	template <class T>
	T&min(const T&a, const T&b)
	{
		return a < b ? a : b;
	}

END_NAMESPACE_MYSTD

#endif //MYSTL_MYSTL_ALGOBASE_H
