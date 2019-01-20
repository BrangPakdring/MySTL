#include <cstdio>
#include "list.h"
#include <list>
using namespace mystd;

int main()
{
	std::list<int>ll;
	ll.begin();

	list<int>l;

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);

	l.push_back(5);
	l.push_back(6);
	l.push_back(7);
	l.push_back(8);

	for (auto i : l)printf("%d\t", i);
	puts("");

	auto it = ++l.begin();
	auto it2 = it, it3 = it;
	++it2, ++++++it3;
	l.transfer(it, it2, it3);

	for(auto i : l)printf("%d\t", i);
	puts("");

	l.reverse();
	for(auto i : l)printf("%d\t", i);
	puts("");
	l.clear();
	return 0;
}