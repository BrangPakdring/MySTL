#include <iostream>
#include <thread>
using std::cout;
using std::endl;

void foo()
{
	std::this_thread::sleep_for(std::chrono::microseconds(200));
	cout << "World" << endl;
}

void bar(int x)
{
	// do stuff...
}

int main()
{
	auto s = std::thread(foo);
	cout << "Hello" << endl;
	s.join();
	return 0;
}