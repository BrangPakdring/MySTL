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

void print(deque<int>&dq)
{
	for (auto&&item : dq)
	{
		cout << item << '\t';
	}
	cout << endl;
}

int main()
{
	vector<int>v = {1,2,3,5,4};

	for (auto &&item : v)
	{
		cout << item << endl;
	}

//	forward_list<int>fl;
//	for (int i = 0; i < 10; ++i)
//	{
//		fl.push_front(i);
//	}
//
//	for (auto it = ++fl.before_begin(); it != fl.end(); ++it)
//	{
//		cout << *it << endl;
//	}
//
//	deque<int>dq;
//	for (int i = 0; i < 50; ++i)
//	{
//		dq.push_back(i);
//		dq.push_front(-i);
//	}
//	print(dq);
//	cout << dq.front() << endl;
//	cout << dq.back() << endl;
//	cout << dq[0] << endl;
//	cout << dq[1] << endl;
//	cout << dq[dq.size() - 1] << endl;
//	cout << dq[dq.size() - 2] << endl;
//	cout << endl;
//	cout << dq.size() << endl;
//	dq.pop_back();
//	cout << dq.size() << endl;
//	print(dq);
//	dq.pop_front();
//	cout << dq.size() << endl;
//	print(dq);
//
//	stack<int>stk;
//	stk.push(1);
//	cout << stk.size() << endl;
//	cout << stk.top() << endl;
//	stk.push(2);
//	cout << stk.size() << endl;
//	cout << stk.top() << endl;
//	stk.pop();
//	cout << stk.size() << endl;
//	cout << stk.top() << endl;
//	stk.pop();
//	cout << stk.size() << endl;
////	cout << stk.top() << endl;
//
//	queue<int>q;
//	q.push(1);
//	cout << q.size() << endl;
//	cout <<q.front() << endl;
//	q.push(2) ;
//	cout << q.size() << endl;
//	cout << q.front() << endl;
//	q.pop();
//	cout << q.size() << endl;
//	cout << q.front() << endl;
//	q.pop();
//	cout << q.size() << endl;
////	cout << q.front() << endl;

}