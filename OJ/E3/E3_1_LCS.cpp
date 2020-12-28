#include <iostream>
#include <cstdlib>
using namespace std;

typedef struct matrix
{
	int num;
	int direct;
} Matrix;

typedef struct
{
	int x;
	int y;
} Points;

int reference[10001];

int LCS(Points *inputArray, int *reference, int lengthA, int lengthB, Matrix *resultMatrix[]);

int pointsCmp(const void *_a, const void *_b);

int MaxNum(int firstNum, int secondNum)
{
	return firstNum > secondNum ? firstNum : secondNum;
}

int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	Points thePoints[10000];
	for (size_t i = 0; i < n; i++)
	{
		cin >> thePoints[i].x >> thePoints[i].y;
	}

	Matrix **resultMatrix = new Matrix *[n + 1];
	for (int i = 0; i < n; i++)
	{
		resultMatrix[i] = new Matrix[10001];
	}

	qsort(thePoints, n, sizeof(Points), pointsCmp);

	for (size_t i = 0; i < 10000; i++)
	{
		reference[i] = i;
	}

	int max = LCS(thePoints, reference, n, 10001, resultMatrix);
	cout << max << endl;
	return 0;
}

int LCS(Points *inputArray, int *reference, int lengthA, int lengthB, Matrix *resultMatrix[])
{
	if (lengthA == 0 || lengthB == 0)
	{
		return 0;
	}
	for (int i = 0; i < lengthA; i++)
	{
		for (int j = 0; j < lengthB; j++)
		{
			resultMatrix[i][j].num = 0;	   //设置所有默认的最长为0
			resultMatrix[i][j].direct = 1; //所有默认方向变成上 0斜上，1上，-1左
		}
	}

	for (int i = 0; i < lengthA; i++)
	{
		for (int j = 0; j < lengthB; j++)
		{
			if (inputArray[i].y == reference[j])
			{
				resultMatrix[i + 1][j + 1].num = resultMatrix[i][j].num + 1;
				resultMatrix[i + 1][j + 1].direct = 0;
			}
			else
			{
				resultMatrix[i + 1][j + 1].num = MaxNum(resultMatrix[i + 1][j].num, resultMatrix[i][j + 1].num);
				resultMatrix[i + 1][j + 1].direct = resultMatrix[i + 1][j].num > resultMatrix[i][j + 1].num ? 1 : -1;
			}
		}
	}
	return resultMatrix[lengthA][lengthB].num;
}

int pointsCmp(const void *_a, const void *_b)
{
	Points *a = (Points *)_a;
	Points *b = (Points *)_b;
	if (a->x != b->x)
	{
		return a->x - b->x;
	}
	else
	{
		return a->y - b->y;
	}
}
