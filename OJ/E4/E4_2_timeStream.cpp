#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define MIN(a, b) (a < b) ? a : b

typedef struct
{
	int arrival;
	int execute;
	int finish;
} Task;

struct Progress
{
	int remaining;
	int taskSeq;
	bool operator<(const Progress &a) const
	{
		return remaining > a.remaining;
	}
};

int taskCmpArrival(const void *_a, const void *_b);

int main(int argc, char const *argv[])
{
	priority_queue<Progress> remainTime;
	// vector<Task> initialTime;
	Task *initialTime;
	int n;
	cin >> n;
	if (n == 0)
	{
		cout << "0" << endl;
		return 0;
	}

	initialTime = new Task[n];
	for (size_t i = 0; i < n; i++)
	{
		cin >> initialTime[i].arrival >> initialTime[i].execute;
	}
	qsort(initialTime, n, sizeof(Task), taskCmpArrival);
	int nowTime = 0;
	int cameTask = 0;

	remainTime.push((Progress){initialTime[cameTask].execute, cameTask});
	nowTime = initialTime[cameTask].arrival - 1;
	cameTask++;

	while (!remainTime.empty())
	{
		nowTime++;
	}

	return 0;
}

int taskCmpArrival(const void *_a, const void *_b)
{
	Task *a = (Task *)_a;
	Task *b = (Task *)_b;
	return a->arrival - b->arrival;
}
