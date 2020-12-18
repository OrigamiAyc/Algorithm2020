/**
 * At first I meant to change the lifespan of a number when it's shot in the cache
 * so I chose min-heap instead of priority queue to store those lifespans
 * since queues cannot be random accessed
 * However it's hard to posite that element in a dynamic set
 * thus I do not pop out when it should be changed out
 * for the old data should be
 **/
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

struct cacheItem
{
	char num;
	int lifespan;
};

/**
 * 10000 is the memory limit
 * in each cell stores the
 **/
int ifCached[10000];

int main(int argc, char const *argv[])
{
	int n, k;
	char *input = new char[n];
	int *inputInt = new int[n];
	vector<cacheItem> buffer;
	make_heap(buffer.begin(), buffer.end());
	// cacheItem *buffer = new cacheItem[k];

	for (size_t i = 0; i < n; i++)
	{
		cin >> inputInt[i];
		input[i] = (char)inputInt[i];
	}
	string inputStrem(input);

	int missTimes = 0;
	for (size_t i = 0; i < n; i++)
	{
		int nextpos = inputStrem.find_first_of(input[i]);
		if (ifCached[inputInt[i]])
		{
			/* code */
		}

	}

	return 0;
}
