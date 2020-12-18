#include <iostream>
using namespace std;

#define NW 0
#define W 1
#define N 2

// typedef struct matrix
// {
// 	short num;
// 	// bool direct;
// } Matrix;

typedef struct
{
	short x;
	short y;
} Points;

// short reference[10002];
int c[2][10010];

void LCS_LengthC(int *x, int m, int n);

// void LCSLength(short *x, int m, int n);

int pointsCmp(const void *_a, const void *_b);

int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	Points *thePoints;
	thePoints = new Points[n + 1];
	for (size_t i = 0; i < n; i++)
	{
		cin >> thePoints[i].x >> thePoints[i].y;
	}

	// c = new Matrix *[n + 1];
	// for (int i = 0; i <= n; i++)
	// {
	// 	c[i] = new Matrix[10002];
	// }

	qsort(thePoints, n, sizeof(Points), pointsCmp);

	int y[n+1];

	for (size_t i = 1; i <= n; i++)
	{
		y[i] = thePoints[i-1].y;
	}

	delete[] thePoints;

	// for (size_t i = 1; i <= 10001; i++)
	// {
	// 	reference[i] = i - 1;
	// }

	LCS_LengthC(y, n, 10001);
	return 0;
}
void LCS_LengthC(int *x, int m, int n)
{
	int i, j;
	bool flag = 0;
	c[1][0] = 0;
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (x[i] == (j - 1))
			{
				c[(int)!flag][j] = c[(int)flag][j - 1] + 1;
			}
			else if (c[(int)flag][j] >= c[(int)!flag][j - 1])
			{
				c[(int)!flag][j] = c[(int)flag][j];
			}
			else
			{
				c[(int)!flag][j] = c[(int)!flag][j - 1];
			}
		}
		flag = !flag;
		for (int k = 1; k <= n; k++)
		{
			c[(int)!flag][k] = 0;
		}
	}
	cout << c[(int)flag][n] << endl;
}

// void LCSLength(short *x, int m, int n)
// {
// 	for (size_t i = 1; i <= m; i++)
// 	{
// 		c[i][0].num = 0;
// 	}
// 	for (size_t i = 1; i <= n; i++)
// 	{
// 		c[0][i].num = 0;
// 	}
// 	for (size_t i = 1; i <= m; i++)
// 	{
// 		for (size_t j = 1; j <= n; j++)
// 		{
// 			if (x[i] == (j - 1))
// 			{
// 				c[i][j].num = c[i - 1][j - 1].num + 1;
// 				// c[i][j].direct = NW;
// 			}
// 			else if (c[i - 1][j].num >= c[i][j - 1].num)
// 			{
// 				c[i][j].num = c[i - 1][j].num;
// 				// c[i][j].direct = N;
// 			}
// 			else
// 			{
// 				c[i][j].num = c[i][j - 1].num;
// 				// c[i][j].direct = W;
// 			}
// 		}
// 	}
// 	cout << c[m][n].num << endl;
// }

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
