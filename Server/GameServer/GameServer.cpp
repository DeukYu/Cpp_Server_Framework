#include "pch.h"
#include <iostream>
#include <thread>

void HelloThread()
{
	cout << "Hello Thread" << endl;
}

void HelloThread_2(int32 num)
{
	cout << num << endl;
}

int main()
{
	std::thread t;

	vector<std::thread> v;

	auto id1 = t.get_id();	// 쓰레드마다 id

	for (int32 i = 0; i < 10; ++i)
	{
		v.push_back(std::thread(HelloThread_2, i));
	}
	
	int32 count = t.hardware_concurrency();	// CPU 코어 개수?
	auto id2 = t.get_id();	// 쓰레드마다 id
	cout << "Hello Main" << endl;
	for (int32 i = 0; i < 10; ++i)
	{
		if (v[i].joinable())
			v[i].join();
	}
}
