#include <iostream>
#include <thread>
#include <list>
using std::cout;
using std::endl;

#include "list.h"
#include "array.h"
using namespace mystd;
int main()
{
	std::list<int>ll = {1,2,3,4};
	ll.begin()._M_node->_M_next = nullptr;
	cout << ll.size() << endl;
	list<int>l;
	l.push_front(1);
	l.push_back(2);
	for (auto it = l.cbegin(); it != l.cend(); ++it)
		cout << (*it) << endl;
}