#include <iostream>
#include <thread>
#include <format>

using namespace std;

int globalNum = 0;
thread_local int tlNum = 0;

void fn1()
{
	++globalNum;
	++tlNum;
	cout << format("<fn1> globalNum : {}", globalNum) << endl;
	cout << format("<fn1> tlNum : {}", tlNum) << endl;
}

void fn2()
{
	++globalNum;
	++tlNum;
	cout << format("<fn2> globalNum : {}", globalNum) << endl;
	cout << format("<fn2> tlNum : {}", tlNum) << endl;
}
int main()
{
	thread t1(fn1);
	thread t2(fn2);

	t1.join();
	t2.join();
	return 0;
}