#include <iostream>
#include <deque>
using std::cout;
using std::endl;

#include "list.h"
#include "stack.h"
#include "queue.h"
#include "array.h"
#include "forward_list.h"
#include "vector.h"

using namespace mystd;

int main()
{
	{
		int ia[] = {0, 1, 2, 3, 4, 8, 9, 5, 3};

		make_heap(ia, ia + 9);
		sort_heap(ia, ia + 9);
		for (auto&i : ia)cout << i << '\t'; cout << endl;

		make_heap(ia, ia + 9);
		pop_heap(ia, ia + 9);
		cout << ia[8] << endl;


	}
	{
		int ia[] = {4,1,7,6,2,5};
		make_heap(ia, ia + 6);
		for (auto&i : ia)cout << i << '\t'; cout << endl;

	}

	int ia[] = {0, 1, 2, 3, 4, 8, 9, 5, 3};
	priority_queue<int>ipq(ia, ia + 9);
	cout << ipq.size() << endl;

	cout << ipq.top() << endl;

	while (!ipq.empty())
	{
		cout << ipq.top() << endl;
		ipq.pop();
	}
}