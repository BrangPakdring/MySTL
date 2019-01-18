//
// Created by brang on 1/18/19.
//

#ifndef MYSTL_TYPE_TRAITS_H
#define MYSTL_TYPE_TRAITS_H

#include "mystl_config.h"

BEGIN_NAMESPACE_MYSTD

struct __true_type{};
struct __false_type{};

template <class>
struct __type_traits
{
	using has_trivial_default_constructor = __false_type;
	using has_trivial_copy_constructor = __false_type;
	using has_trivial_assignment_operator = __false_type;
	using has_trivial_destructor = __false_type;
	using is_POD_type = __false_type;
};

template <>
struct __type_traits<char>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

template <>
struct __type_traits<signed char>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

template <>
struct __type_traits<unsigned char>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

template <>
struct __type_traits<short>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

template <>
struct __type_traits<unsigned short>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

template <>
struct __type_traits<int>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

template <>
struct __type_traits<unsigned int>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

template <>
struct __type_traits<long>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

template <>
struct __type_traits<unsigned long>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

template <>
struct __type_traits<long long>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

template <>
struct __type_traits<unsigned long long>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

template <>
struct __type_traits<float>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

template <>
struct __type_traits<double>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

template <>
struct __type_traits<long double>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

template <class T>
struct __type_traits<T*>
{
	using has_trivial_default_constructor = __true_type;
	using has_trivial_copy_constructor = __true_type;
	using has_trivial_assignment_operator = __true_type;
	using has_trivial_destructor = __true_type;
	using is_POD_type = __true_type;
};

END_NAMESPACE_MYSTD

#endif //MYSTL_TYPE_TRAITS_H
