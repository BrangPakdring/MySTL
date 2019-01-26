//
// Created by brang on 1/22/19.
//

#ifndef MYSTL_STACK_H
#define MYSTL_STACK_H

#include "mystl_config.h"
#include "deque.h"

BEGIN_NAMESPACE_MYSTD

	template <class T, class Sequence = deque<T>>
	class stack
	{
	public:
		typedef typename Sequence::value_type value_type;
		typedef typename Sequence::size_type size_type;
		typedef typename Sequence::reference reference;
		typedef typename Sequence::const_reference const_reference;
	protected
		Sequence c;
	public:
		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}

		reference top()
		{
			return c.back();
		}

		const_reference top() const
		{
			return c.back();
		}

		void push(const value_type &x)
		{
			c.push_back(x);
		}

		void pop()
		{
			c.pop_back();
		}

		bool operator==(const stack &x) const
		{
			return c == x.c;
		}

		bool operator<(const stack &x) const
		{
			return c < x.c;
		}
	};

END_NAMESPACE_MYSTD

#endif //MYSTL_STACK_H
