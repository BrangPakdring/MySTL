//
// Created by brang on 1/18/19.
//

#include "mystl_config.h"

#ifndef MYSTL_VECTOR_H
#define MYSTL_VECTOR_H

template <class T, class Alloc = alloc>
class vector
{
public:
	using value_type = T;
	using pointer = value_type *;
	using iterator = value_type *;
	using reference = value_type &;
	using size_type = size_t;
protected:

};

#endif //MYSTL_VECTOR_H
