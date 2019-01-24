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

		vector<int> ivec(ia, ia + 9);

		for (int i = 0; i < ivec.size(); ++i)cout << ivec[i] << '\t';
		cout << endl;

		make_heap(ivec.begin(), ivec.end());

		for (int i = 0; i < ivec.size(); ++i)cout << ivec[i] << '\t';
		cout << endl;

		ivec.push_back(7);
		push_heap(ivec.begin(), ivec.end());
		for (int i = 0; i < ivec.size(); ++i)cout << ivec[i] << '\t';
		cout << endl;

		pop_heap(ivec.begin(), ivec.end());
		cout << ivec.back() << endl;
		ivec.pop_back();

		for (int i = 0; i < ivec.size(); ++i)cout << ivec[i] << '\t';
		cout << endl;

		sort_heap(ivec.begin(), ivec.end());
		for (int i = 0; i < ivec.size(); ++i)cout << ivec[i] << '\t';
		cout << endl;
	}

}