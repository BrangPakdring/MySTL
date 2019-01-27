//
// Created by brang on 1/27/19.
//

#ifndef MYSTL_MYSTL_HASHTABLE_H
#define MYSTL_MYSTL_HASHTABLE_H

#include "mystl_config.h"
#include "mystl_allocator.h"
#include "mystl_algo.h"
#include "vector.h"

BEGIN_NAMESPACE_MYSTD

	constexpr static const int __stl_num_primes = 28;
	constexpr static const unsigned long __stl_prime_list[__stl_num_primes] =
			{
					53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433,
					1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457,
					1610612741, 3221225473UL, 4294967291UL
			};

	inline unsigned long __stl_next_prime(unsigned long n)
	{
		const unsigned long*first = __stl_prime_list;
		const unsigned long*last = __stl_prime_list + __stl_num_primes;
		const unsigned long*pos = lower_bound(first, last, n);
		return pos == last ? *(last - 1) : *pos;
	}

	template <class T>
	struct __hashtable_node
	{
		__hashtable_node *next;
		T value;
	};

	template <class Val, class Key, class HashFunc, class ExtractKey, class EqualKey, class Alloc = allocator<Val>>
	class hashtable
	{
	public:
		typedef HashFunc hasher;
		typedef EqualKey key_equal;
		typedef size_t size_type;
		typedef Val value_type;
	private:
		hasher hash;
		key_equal equals;
		ExtractKey get_key;
		typedef __hashtable_node<Val> node;
		typedef simple_alloc<node, Alloc> node_allocator;
		vector<node *, Alloc> buckets;
		size_type num_elements;
	public:
		size_type bucket_count() const
		{
			return buckets.size();
		}

		size_type max_bucket_count() const
		{
			return __stl_prime_list[__stl_num_primes - 1];
		}

	protected:
		node*new_node(const value_type&obj)
		{
			node*n = node_allocator::allocate();
			n->next = nullptr;
			try
			{
				construct(&n->value, obj);
			}
			catch (...)
			{
				node_allocator::deallocate(n);
				throw;
			}
			return n;
		}

		void delete_node(node*n)
		{
			destroy(n);
			node_allocator::deallocate(n);
		}

		size_type next_size(size_type n) const
		{
			return __stl_next_prime(n);
		}

		void initialize_buckets(size_type n)
		{
			const size_type n_buckets = next_size(n);
			buckets.reserve(n_buckets);
			buckets.insert(buckets.end(), n_buckets, (node*)0);
			num_elements = 0;
		}

	public:
		hashtable(size_type n, const hasher&hf, const key_equal&eql)
		: hasher (hf), equals(eql), get_key(ExtractKey()), num_elements()
		{
			initialize_buckets(n);
		}
	};

	template <class Val, class Key, class HashFunc, class ExtractKey, class EqualKey, class Alloc>
	struct __hashtable_iterator
	{
		typedef __hashtable_iterator self;
		typedef hashtable<Val, Key, HashFunc, ExtractKey, EqualKey, Alloc> hashtable;
		typedef __hashtable_iterator iterator;
		typedef __hashtable_node<Val> node;
		typedef forward_iterator_tag iterator_category;
		typedef Val value_type;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef Val &reference;
		typedef Val *pointer;

		node *cur;
		hashtable *ht;

		__hashtable_iterator(node *n, hashtable *ht) : cur(n), ht(ht)
		{}

		__hashtable_iterator() = default;

		reference operator*() const
		{
			return cur->value;
		}

		pointer operator->() const
		{
			return &operator*();
		}

		self &operator++()
		{
			const node *old = cur;
			cur = cur->next;
			if (cur == nullptr)
			{
				size_type bucket = ht->bkt_num(old->value);
				while (cur == nullptr && ++bucket < ht->buckets.size())
					cur = ht->buckets[bucket];
			}
			return *this;
		}

		const self operator++(int)
		{
			self tmp = *this;
			++*this;
			return tmp;
		}

		bool operator==(const iterator &it) const
		{
			return cur == it.cur;
		}

		bool operator!=(const iterator &it) const
		{
			return cur != it.cur;
		}
	};


END_NAMESPACE_MYSTD

#endif //MYSTL_MYSTL_HASHTABLE_H
