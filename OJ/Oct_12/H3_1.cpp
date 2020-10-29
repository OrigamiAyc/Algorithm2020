// 描述
// 给定n个整数，请统计出每个整数出现的次数，按出现次数从多到少的顺序输出。

#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct
{
	int data;
	int frequency;
} key;

int frequency_cmp(const void *_a, const void *_b);

int main(int argc, char const *argv[])
{
	int n = 0; // amount
	cin >> n;
	if (n == 0)
	{
		printf("NO DATA ERROR\n");
		exit(1);
	}

	key *statistics = new key[n];
	int first;
	cin >> first;
	statistics[0].data = first;
	statistics[0].frequency = 1;
	int stored = 1; // the amount of known keywords
	for (size_t i = 1; i < n; i++)
	{
		int temp;
		cin >> temp;
		bool ifFound = false;
		for (size_t j = 0; j < stored; j++)
		{
			if (statistics[j].data == temp)
			{
				statistics[j].frequency++;
				ifFound = true;
				break;
			}
		}
		if (!ifFound)
		{
			statistics[stored].data = temp;
			statistics[stored].frequency = 1;
			stored++;
		}
	}
	qsort(statistics, stored, sizeof(key), frequency_cmp);
	for (size_t i = 0; i < stored; i++)
	{
		cout << statistics[i].data << " " << statistics[i].frequency << endl;
	}

	return 0;
}

int frequency_cmp(const void *_a, const void *_b)
{
	key *a = (key *)_a;
	key *b = (key *)_b;
	if (a->frequency != b->frequency)
	{
		return b->frequency - a->frequency;
	}
	else
	{
		return a->data - b->data;
	}
}
