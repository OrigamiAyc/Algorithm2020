#include "cstdio"
#include "iostream"
#include "cstring"
using namespace std;

int ne[20];			  ///这个数组中盛放的是匹配字符串的next值
void GetNext(char *a) ///这个函数是为了标记匹配字符串的next值
{
	int len = strlen(a); ///先求字符串的长度，便于循环赋值
	int i = 0, j = -1;
	ne[0] = -1;
	while (i < len)
	{
		if (j == -1 || a[i] == a[j])
		{
			ne[++i] = ++j;
		}
		else
			j = ne[j];
	}
}
///实际上每求一个next值要循环两遍
int KMP(char *a, char *b)
{
	int lena = strlen(a);
	int lenb = strlen(b);
	int i = 0, j = 0;
	int count = 0;
	while (i < lena && j < lenb)
	{
		if (j == -1 || a[i] == b[j])
		{
			j++;
			i++;
		}
		else
			j = ne[j];
		if (j == lenb)
		{
			count++;
			j = 0;
			i -= (lenb - 1);
		}
	}
	return count;
	// if (j == lenb)
	// 	return i - j + 1;
	// else
	// 	return -1;
}

int main()
{
	char s[100]; ///this is the main
	char f[100]; ///this is the one to be found
	int t;
	cin >> t;
	for (size_t i = 0; i < t; i++)
	{
		scanf("%s", f);
		scanf("%s", s);
		GetNext(f);
		cout << KMP(s, f) << endl;
	}

	return 0;
}
