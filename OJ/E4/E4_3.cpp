/**
 * At first I meant to change the lifespan of a number when it's shot in the cache
 * so I chose max-heap instead of priority queue to store those lifespans
 * since queues cannot be random accessed
 * However it's hard to posite that element in a dynamic set
 * thus I do not pop out when it should be changed out
 * for the old data should never be heap top
 **/
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

#define INF 1000000
// #define INF 2147483647

struct cacheItem
{
	int lifespan;
	int num;
	bool operator<(cacheItem a) const
	{
		return lifespan < a.lifespan;
	}
};

/**
 * 10000 is the memory limit
 * I didn't mem the next position since I used the string func
 **/
bool ifCached[10001];

class less_class
{
public:
	bool operator()(cacheItem a, cacheItem b)
	{
		return a.lifespan < b.lifespan;
	}
};

int main(int argc, char const *argv[])
{
	int n, k;
	cin >> n >> k;
	memset(ifCached, 0, sizeof(ifCached));
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
	string inputStream(input);
	/** NOTE:
	 * Cannot use buffer.size() directly
	 * since we've pushed item inside buffer when is already in there
	 * the buffer.size() can reach k even if there have not been k different items
	 **/
	// int bufferSize = 0;

	int missTimes = 0;
	for (size_t i = 0; i < n; i++)
	{
		int nextpos = inputStream.find(input[i], i + 1);
		// cout << "firstof " << inputInt[i] << " is " << nextpos << endl;
		if (ifCached[inputInt[i]])
		/**
		 * push a new item with its arguments instead of changing the original element
		 * This will not have an impact on the heap
		 * since what we kick out is always the one with the largest lifespan
		 * the small (actually already visited) time num does not matter
		 **/
		{
			int lifespan = (nextpos == -1) ? INF : nextpos;
			buffer.push_back((cacheItem){lifespan, inputInt[i]});
			push_heap(buffer.begin(), buffer.end());
			// OR we can just let k soar
			k++;
		}
		else if (/* bufferSize */ buffer.size() < k)
		// The buffer is not full yet
		{
			missTimes++;
			int lifespan = (nextpos == -1) ? INF : nextpos;
			buffer.push_back((cacheItem){lifespan, inputInt[i]});
			push_heap(buffer.begin(), buffer.end());
			ifCached[inputInt[i]] = true;
			// bufferSize++;
			// cout << "bufferSize = " << bufferSize << endl;
		}
		else
		// Buffer full, need to kick out the heap top
		{
			cacheItem heapPop = buffer.front();
			// cout << "now poped is " << heapPop.num << endl;
			pop_heap(buffer.begin(), buffer.end());
			buffer.pop_back();
			ifCached[heapPop.num] = false;
			missTimes++;
			int lifespan = (nextpos == -1) ? INF : nextpos;
			buffer.push_back((cacheItem){lifespan, inputInt[i]});
			push_heap(buffer.begin(), buffer.end());
			ifCached[inputInt[i]] = true;
		}
		// ifCached[inputInt[i]] = true;
	}
	cout << missTimes << endl;
	return 0;
}
