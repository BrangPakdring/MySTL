#define protected public
#define private public

#include "vector.h"
#include <vector>
#include <iostream>
#include <queue>
#include "mystl_numeric.h"
#include "algorithm.h"
#include "vector.h"
#include "deque.h"
#include "queue.h"

void test_std()
{
	using namespace std;
	queue<int>q;
	vector<int>v;
	deque<int>dq = {1,2};
	dq.begin();
	cout << *lower_bound(dq.begin(), dq.end(), 0) << endl;
	cout << v.capacity() << '\t' << v.size() << endl;
	v.push_back(1);
	cout << v.capacity() << '\t' << v.size() << endl;
	v.push_back(2);
	cout << v.capacity() << '\t' << v.size() << endl;
	for (auto&&i : v)cout << i << '\t'; cout << endl;
	v.reserve(11);
	cout << v.capacity() << '\t' << v.size() << endl;
	for (auto&&i : v)cout << i << '\t'; cout << endl;
	cout << *min_element(dq.begin(), dq.end()) << endl;
}

void test_mystd()
{
	using namespace mystd;
	using std::cout;
	using std::endl;
	using std::cin;
	queue<int>q;
	vector<int>v;
	deque<int>dq = {1,2};
	dq.begin();
	cout << *lower_bound(dq.begin(), dq.end(), 0) << endl;
	cout << v.capacity() << '\t' << v.size() << endl;
	v.push_back(1);
	cout << v.capacity() << '\t' << v.size() << endl;
	v.push_back(2);
	cout << v.capacity() << '\t' << v.size() << endl;
	for (auto&&i : v)cout << i << '\t'; cout << endl;
	v.reserve(11);
	cout << v.capacity() << '\t' << v.size() << endl;
	for (auto&&i : v)cout << i << '\t'; cout << endl;
	cout << *min_element(dq.begin(), dq.end()) << endl;
}

int main()
{
	test_std();
	test_mystd();
}
