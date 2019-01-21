#include <iostream>
#include <thread>
using std::cout;
using std::endl;

#include "list.h"
int main()
{
	using namespace mystd;
	list<int>l;
	l.push_front(1);
	l.push_back(2);
	for (auto it = l.cbegin(); it != l.cend(); ++it)
		cout << (*it) << endl;
}