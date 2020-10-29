#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct
{
	int number;
	int maths;
	int english;
	int total;
} student;

int score_cmp(const void *_a, const void *_b);

int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	if (n == 0)
	{
		printf("NO DATA ERROR\n");
		exit(1);
	}

	student *score = new student[n];
	for (size_t i = 0; i < n; i++)
	{
		cin >> score[i].number >> score[i].maths >> score[i].english;
		score[i].total = score[i].maths + score[i].english;
	}
	qsort(score, n, sizeof(student), score_cmp);
	for (size_t i = 0; i < n; i++)
	{
		cout << score[i].number << " ";
	}
	cout << endl;
	return 0;
}

int score_cmp(const void *_a, const void *_b)
{
	student *a = (student *)_a;
	student *b = (student *)_b;
	if (a->total != b->total)
	{
		return b->total - a->total;
	}
	else if (a->maths != b->maths)
	{
		return b->maths - a->maths;
	}
	else if (a->english != b->english)
	{
		return b->english - a->english;
	}
	else
	{
		return b->number - a->number;
	}
}
