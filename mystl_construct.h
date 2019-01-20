//
// Created by brang on 1/18/19.
//

#ifndef MYSTL_MYSTL_CONSTRUCT_H
#define MYSTL_MYSTL_CONSTRUCT_H

#include "mystl_config.h"
#include "type_traits.h"
#include <new>

BEGIN_NAMESPACE_MYSTD

	template <class T>
	inline T*allocate(ptrdiff_t size, T*)
	{
		T*tmp = (T*)::operator new((size_t)(size * sizeof(T)));
		if (!tmp)
		{
			exit(1);
		}
		return tmp;
	}

	template <class T>
	inline void deallocate(T*buf)
	{
		::operator delete(buf);
	}

	template <class T1, class T2>
	inline void construct(T1*p, const T2&value)
	{
		new(p)T1(value);
	}

	template <class T>
	inline void destroy(T*p)
	{
		p->~T();
	}

	template<class ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last)
	{
		__destroy(first, last, value_type(first));
	}

	template<class ForwardIterator, class T>
	inline void __destroy(ForwardIterator first, ForwardIterator last, T *)
	{
		using trivial_destructor = typename __type_traits<T>::has_trivial_destructor;
		__destroy_aux(first, last, trivial_destructor());
	}

	template<class ForwardIterator, class T>
	inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __false_type)
	{
		while (first != last)
		{
			destroy(&*first);
			++first;
		}
	}

	template<class ForwardIterator>
	inline void __destroy_aux(ForwardIterator, ForwardIterator, __true_type)
	{

	}


END_NAMESPACE_MYSTD

#endif //MYSTL_MYSTL_CONSTRUCT_H
