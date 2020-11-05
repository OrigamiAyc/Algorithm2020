#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmpMoney(const int &a, const int &b)
{
	return a > b;
}

typedef struct heapNode
{
	int money;
	int daySequence;
} heapNode;

int main(int argc, char const *argv[])
{
	heapNode *days;
	vector<heapNode> max_heap(days, days + 1000000);
	int n, k;
	cin >> n >> k;
	make_heap(max_heap.begin(), max_heap.end());
	for (size_t i = 0; i < k; i++) // push in first k days
	{
		heapNode newDay;
		cin >> newDay.money;
		newDay.daySequence = i + 1;
		max_heap.push_back(newDay);
		push_heap(max_heap.begin(), max_heap.end());
	}
	for (size_t i = k; i < n; i++)
	{

	}


	return 0;
}
