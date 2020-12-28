#include <iostream>
#include <cstdio>
using namespace std;

// #define max((a), (b)) (a > b) ? a : b

int max(int a, int b)
{
	return a > b ? a : b;
}

typedef struct
{
	int weighti;
	int value;
} Thing;

Thing list[2000000];

int dp[10001];

int main()
{
	int weight, n; //背包容量和物品总数
	scanf("%d %d", &n, &weight);
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		int wei, val, num;
		scanf("%d %d %d", &wei, &val, &num);
		int numinPack = 1;
		while (num > 0)
		{
			list[count].value = val * numinPack;
			list[count].weighti = wei * numinPack;
			num -= numinPack;
			if (num >= (numinPack * 2))
			{
				numinPack *= 2;
			}
			else
			{
				numinPack = num;
			}
			count++;
		}
	}
	for (int i = 0; i <= weight; i++)
		dp[i] = 0;
	for (int i = 0; i < count; i++)
	{
		for (int j = weight; j >= list[i].weighti; j--)
		{
			dp[j] = max(dp[j], dp[j - list[i].weighti] + list[i].value);
		}
	}
	printf("%d\n", dp[weight]);
	return 0;
}
