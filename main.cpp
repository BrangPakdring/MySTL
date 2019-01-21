#include <iostream>
#include "list.h"
#include <list>
#include <algorithm>
#include "mystl_function.h"
using namespace mystd;
using std::cout;
using std::endl;

#include <functional>
int main()
{
	cout << plus<int>()(1, 2) << endl;
}