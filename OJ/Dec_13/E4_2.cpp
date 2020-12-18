/**
 * use a min heap
 * count by time piece
 **/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define MIN(a, b) (a < b) ? a : b

typedef struct task
{
	int arrival;
	int execute;
	int finish;
	bool operator<(const task &b) const
	{
		return arrival < b.arrival;
	};
} Task;

typedef struct progress
{
	int remaining;
	int taskSeq;
	bool operator<(const progress &a) const
	{
		return remaining > a.remaining;
	}
} Progress;

class greater_class
{
public:
	bool operator()(Progress a, Progress b)
	{
		return a.remaining > b.remaining;
	}
};

bool taskCmpArrival(Task *a, Task *b);

int main(int argc, char const *argv[])
{
	vector<Progress> remainTime;
	make_heap(remainTime.begin(), remainTime.end(), greater_class());
	// vector<Task> initialTime;
	//Task *initialTime;
	int n;
	cin >> n;
	if (n == 0)
	{
		cout << "0" << endl;
		return 0;
	}

	vector<Task> initialTime(n); //= new Task[n];
	for (size_t i = 0; i < n; i++)
	{
		cin >> initialTime[i].arrival >> initialTime[i].execute;
	}
	sort(initialTime.begin(), initialTime.end() /*, taskCmpArrival*/);
	initialTime.push_back((Task){initialTime[n - 1].arrival + initialTime[n - 1].execute + 10, 0, 0});
	int nowTime = 0;
	int cameTask = 0;

	remainTime.push_back((Progress){initialTime[cameTask].execute, cameTask});
	push_heap(remainTime.begin(), remainTime.end(), greater_class());
	nowTime = initialTime[cameTask].arrival;
	cameTask++;

	while ((!remainTime.empty()) || (cameTask <= n))
	{
		/* status change according to incidents (arrival or complete) */
		Progress heapTop = remainTime.front();
		while (heapTop.remaining <= (initialTime[cameTask].arrival - nowTime))
		{
			/* complete current task */
			nowTime += heapTop.remaining;
			initialTime[heapTop.taskSeq].finish = nowTime;
			pop_heap(remainTime.begin(), remainTime.end());
			remainTime.pop_back();
			if (remainTime.empty())
			{
				break;
			}
			heapTop = remainTime.front();
		}
		if (cameTask == n) // all tasks are in
		{
			while (!remainTime.empty())
			{
				/* complete current task */
				heapTop = remainTime.front();
				nowTime += heapTop.remaining;
				initialTime[heapTop.taskSeq].finish = nowTime;
				pop_heap(remainTime.begin(), remainTime.end());
				remainTime.pop_back();
			}
			break;
		}
		// take in a new task
		if (!remainTime.empty())
		{
			remainTime.front().remaining -= (initialTime[cameTask].arrival - nowTime);
		}
		remainTime.push_back((Progress){initialTime[cameTask].execute, cameTask});
		push_heap(remainTime.begin(), remainTime.end(), greater_class());
		nowTime = initialTime[cameTask].arrival;
		cameTask++;
	}

	int respondTime = 0;
	for (size_t i = 0; i < n; i++)
	{
		// cout << "arrival[" << i << "] = " << initialTime[i].arrival << endl;
		// cout << "execute[" << i << "] = " << initialTime[i].execute << endl;
		// cout << "finish[" << i << "] = " << initialTime[i].finish << endl;
		respondTime += (initialTime[i].finish - initialTime[i].arrival /* + 1*/);
	}
	cout << respondTime << endl;
	return 0;
}

bool taskCmpArrival(Task *a, Task *b)
{
	if (a->execute != b->execute)
	{
		return a->arrival < b->arrival; // from min to max
	}
	else
	{
		return a->execute < b->execute;
	}
}
