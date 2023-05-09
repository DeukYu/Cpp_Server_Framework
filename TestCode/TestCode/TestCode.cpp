#include <iostream>
#include <unordered_map>

using namespace std;

int main() 
{
	unordered_map<int, int> testuMap;

	for (int i = 1; i < 100; ++i)
	{
		testuMap.insert({ i, i * 10 });
	}
	cout << testuMap.load_factor() << endl;
	return 0;
}