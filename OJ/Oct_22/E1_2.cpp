#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
const int N = 1000000;

long a[N], tmp[N];
long long ans;

void Merge(int l, int m, int r) // merge two arrays [l-m] and [m+1,r]
{
	int i = l;
	int j = m + 1;
	int k = l;
	while (i <= m && j <= r)
	{
		if (a[i] > a[j])
		{
			tmp[k++] = a[j++];
			ans += m - i + 1;
		}
		else
		{
			tmp[k++] = a[i++];
		}
	}
	while (i <= m)
		tmp[k++] = a[i++];
	while (j <= r)
		tmp[k++] = a[j++];
	for (int i = l; i <= r; i++)
		a[i] = tmp[i];
}

void Merge_sort(int l, int r)
{
	if (l < r)
	{
		int m = (l + r) >> 1;
		Merge_sort(l, m);
		Merge_sort(m + 1, r);
		Merge(l, m, r);
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	ans = 0;
	Merge_sort(0, n - 1);
	printf("%d\n", ans%10000019);
	return 0;
}
