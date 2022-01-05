#include "pch.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>

vector<int32>	v;
// Mutual Exclusive (상호베타적)
mutex m;

// RAII (Resource Acquisition is Initialization)
template<typename T>
class LockGuard
{
public:
	LockGuard(T& m)
	{
		_mutex = &m;
		_mutex->lock();
	}

	~LockGuard()
	{
		_mutex->unlock();
	}
private:
	T* _mutex;
};

void Push()
{
	for (int32 i = 0; i < 10'000; ++i)
	{
		//std::lock_guard<std::mutex>	lockGuard(m);
		std::unique_lock<std::mutex>	uniqueLock(m, std::defer_lock);
		uniqueLock.lock();
		if (i == 5000)
		{
			break;
		}
	}
}

int main()
{
	std::thread t1(Push);
	std::thread t2(Push);

	t1.join();
	t2.join();

	cout << v.size() << endl;
}
