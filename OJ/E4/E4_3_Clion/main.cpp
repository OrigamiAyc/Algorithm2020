#include <iostream>
#include "vector"
#include "algorithm"
#include "cstring"
using namespace std;
typedef struct task{
	int task_seq;
	int visit_times = 0;
	vector<int>arr_seq;
}task;
bool cmp(task a,task b)
{
	return a.arr_seq[a.visit_times] < b.arr_seq[b.visit_times];
}
int main() {
	int n,k;//k is the size of memory
	cin >> n >> k;
	vector<task>task_info(10001);
	int task_stream[2*n];
	memset(task_stream,0,sizeof(int)*(2*n));
	int task_num = 0;
	for (int i = 0; i < n; ++i) {
		cin >> task_num;
		task_info[task_num].arr_seq.push_back(i);
		task_info[task_num].task_seq = task_num;
		task_stream[i] = task_num;
	}

	for (int i = 0; i < task_info.size(); ++i) {
		task_info[i].arr_seq.push_back(11000);
	}
	vector<task>mem;
	int miss_time = 0;
	int hit = 0;
	for (int m = 0;m < n;m++) {//coming task
		auto i = task_stream[m];
		if (mem.size() < k) {//mem space not fully occupied
			for (auto j : mem) {//check if hit
				if (j.task_seq == i)//hit
				{
					j.visit_times++;
					task_info[i].visit_times++;
					hit = 1;
					break;
				}
			}
			if (hit == 0)//not hit
			{
				task_info[i].visit_times++;
				mem.push_back(task_info[i]);//take in
				miss_time++;
			}
		}
		else if (mem.size() == k)//mem fully occupied
		{
			//if hit
			for (auto j : mem) {//check if hit
				if (j.task_seq == i)//hit
				{
					j.visit_times++;
					task_info[i].visit_times++;
					hit = 1;
					break;//break for
				}
			}
			//if miss
			if (hit == 0)
			{
				miss_time++;
				//because the space is fully occupied,so we need to swap
				sort(mem.begin(),mem.end(),cmp);
				//swap out the longest will not use
				mem.pop_back();
				//take in new task
				task_info[i].visit_times++;
				mem.push_back(task_info[i]);
			}
		}
		else if (mem.size() > k)
		{
			cout << "error";
			exit(0);
		}
		hit = 0;//reset
	}
	cout << miss_time << endl;
	return 0;
}