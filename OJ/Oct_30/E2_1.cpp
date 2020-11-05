#include <iostream>
#include <map>
#include "cstring"
using namespace std;
int main()
{
	std::ios::sync_with_stdio(false);
	map<int, int> my_map;
	string operation;
	int id = 0;
	int a = 0;
	cin >> operation;
	while (operation != "EXIT")
	{
		if (operation == "INSERT")
		{
			cin >> id >> a;
			my_map.insert(pair<int, int>(a, id));
		}
		else if (operation == "FIND")
		{
			cin >> a;
			map<int, int>::iterator iter;
			iter = my_map.find(a);
			if (iter != my_map.end())
				printf("%d\n", iter->second);
			else
				printf("-1\n");
		}
		cin >> operation;
	}

	return 0;
}
