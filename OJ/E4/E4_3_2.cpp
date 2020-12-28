/**
 * use an array to store the 'next' of every memory item
 * use a priority queue to store the 'next' time of each item in the cache
 * since items in queue cannot be randomly accessed, we use an ordinary vector to store them
 **/
/**
* At first I meant to change the lifespan of a number when it's shot in the cache
* so I chose max-heap instead of priority queue to store those lifespans
* since queues cannot be random accessed
* However it's hard to posit that element in a dynamic set
* thus I do not pop out when it should be changed out
* for the old data should never be heap top
**/

#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

#define INF 1000000

struct cacheItem
{
	int num;
	int next;
	bool operator<(cacheItem a) const
	{
		return next < a.next;
	}
};

/**
 * 10000 is the memory limit
 * I didn't mem the next position since I used the string func
 **/
bool ifCached[10001];

int main(int argc, const char *argv[])
{
	int n, k;
	cin >> n >> k;
	memset(ifCached, 0, sizeof(ifCached));
	cacheItem *input = new cacheItem[n];
	int memHash[10001];
	vector<cacheItem> buffer;
	make_heap(buffer.begin(), buffer.end());

	for (int i = 0; i < 10001; ++i)
	{
		memHash[i] = INF;
	}

	for (size_t i = 0; i < n; ++i)
	{
		cin >> input[i].num;
		input[i].next = INF;
	}
	/** NOTE:
     * when looking from end to front, we record the position of every memory block in memHash[],
     * after retrieving what we stored there before
     */
	for (int i = n - 1; i >= 0; --i)
	{
		input[i].next = memHash[input[i].num];
		memHash[input[i].num] = i;
	}

	int missTimes = 0;
	for (int i = 0; i < n; ++i)
	{
		if (ifCached[input[i].num])
		// cache hit, need to change 'next' region in buffer
		{
			// for (int j = 0; j < buffer.size(); ++j) {
			// 	if (buffer[j].num == input[i].num)
			// 	{
			// 		buffer[j].next = input[i].next;
			// 		break;
			// 	}
			// }
			buffer.push_back(input[i]);
			push_heap(buffer.begin(), buffer.end());
			k++;
		}
		else if (buffer.size() < k)
		// cache not full
		{
			buffer.push_back(input[i]);
			push_heap(buffer.begin(), buffer.end());
			ifCached[input[i].num] = true;
			missTimes++;
		}
		else
		{
			pop_heap(buffer.begin(), buffer.end());
			cacheItem heapTop = buffer.back();
			buffer.pop_back();
			ifCached[heapTop.num] = false;
			buffer.push_back(input[i]);
			push_heap(buffer.begin(), buffer.end());
			ifCached[input[i].num] = true;
			missTimes++;
		}
		// for (size_t i = 0; i < buffer.size(); i++)
		// {
		// 	cout << "buffer[i].num = " << buffer[i].num << endl;
		// 	cout << "buffer[i].next = " << buffer[i].next << endl;
		// }
	}
	cout << missTimes << endl;
	return 0;
}
