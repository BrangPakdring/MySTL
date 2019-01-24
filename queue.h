//
// Created by brang on 1/22/19.
//

#ifndef MYSTL_QUEUE_H
#define MYSTL_QUEUE_H

#include "mystl_config.h"
#include "deque.h"
#include "vector.h"
#include "functional.h"

BEGIN_NAMESPACE_MYSTD

	template <class T, class Sequence = deque<T>>
	class queue
	{
	public:
		typedef typename Sequence::value_type value_type;
		typedef typename Sequence::size_type size_type;
		typedef typename Sequence::reference reference;
		typedef typename Sequence::const_reference const_reference;
	ACCESSIBILITY(protected):
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

		reference front()
		{
			return c.front();
		}

		const_reference front() const
		{
			return c.front();
		}

		void push(const value_type &x)
		{
			c.push_back(x);
		}

		void pop()
		{
			c.pop_front();
		}

		bool operator==(const queue &x) const
		{
			return c == x.c;
		}

		bool operator<(const queue &x) const
		{
			return c < x.c;
		}
	};

	template <class T, class Sequence = vector<T>, class Compare = less<typename Sequence::value_type>>
	class priority_queue
	{
	public:
		typedef typename Sequence::value_type value_type;
		typedef typename Sequence::size_type size_type;
		typedef typename Sequence::reference reference;
		typedef typename Sequence::const_reference const_reference;
	ACCESSIBILITY(protected):
		Sequence c;
		Compare comp;
	public:
		priority_queue() : c(), comp()
		{}

		explicit priority_queue(const Compare &x) : c(), comp(x)
		{}

		template <class InputIterator>
		priority_queue(InputIterator first, InputIterator last, const Compare &x):c(first, last), comp(x)
		{
			make_heap(c.begin(), c.end(), comp);
		}

		template <class InputIterator>
		priority_queue(InputIterator first, InputIterator last):c(first, last), comp()
		{
			make_heap(c.begin(), c.end());
		}

		bool empty() const
		{
			return c.empty();
		}

		size_type size() const
		{
			return c.size();
		}

		const_reference top() const
		{
			return c.front();
		}

		void push(const value_type& x)
		{
			try
			{
				c.push_back(x);
				push_heap(c.begin(), c.end(), comp);
			}
			catch (...)
			{
				throw;
			}
		}

		void pop()
		{
			try
			{
				pop_heap(c.begin(), c.end(), comp);
				c.pop_back();
			}
			catch (...)
			{
				throw;
			}
		}
	};

END_NAMESPACE_MYSTD

#endif //MYSTL_QUEUE_H
