#include <iostream>
#include "list.h"
#include <list>
#include <algorithm>
#include <array>
#include "mystl_function.h"
#include <functional>
#include "array.h"
using namespace mystd;
using std::cout;
using std::endl;

int main()
{
	array<int, 10>aaa = {1,2,3,4};
	aaa.at(1) = 1;
	for (auto&i : aaa)
		cout << i << '\t';
	std::array<int, 10>a = std::array<int, 10>({1}),b ;
	a = b;
	a.at(1);
	int aa[0];
}