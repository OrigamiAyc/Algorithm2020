#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

class Solution
{
private:
	/* data */
public:
	Solution(/* args */);
	void get_next(const char *T, int *next_val);
	int kmp(const char *S, const char *T);
	~Solution();
};

Solution::Solution(/* args */)
{
}

void Solution::get_next(const char *T, int *next_val)
{
	int i = 0;
	int j = -1;
	for (size_t i = 0; i < strlen(T); i++)
	{
		next_val[i] = -1;
	}

	while (i < strlen(T) - 1)
	{
		if ((j == -1) || (T[i] == T[j]))
		{
			i++;
			j++;
			if (i < strlen(T) && (T[i] != T[j]))
			{
				next_val[i] = j;
			}
			else
			{
				next_val[i] = next_val[j];
			}
		}
		else
		{
			j = next_val[j];
		}
	}
	return;
}

int Solution::kmp(const char *S, const char *T)
{
	int i = 0;
	int j = 0;
	int next[strlen(T)];
	this->get_next(T, next);
	int count = 0;
	while ((i < strlen(S)) && (j < strlen(T)))
	{
		if ((j == -1) || (S[i] == T[j]))
		{
			i++;
			j++;
		}
		else if (j == 0)
		{
			i++;
		}
		else
		{
			j = next[j];
		}
		if (j == strlen(T))
		{
			count++;
			j = 0;
			i -= (strlen(T) - 1);
		}
	}
	return count;
}

Solution::~Solution()
{
}

int main(int argc, char const *argv[])
{
	int t;
	cin >> t;
	char *S = new char[1000010];
	char *T = new char[10010];
	Solution sol = Solution();
	for (size_t i = 0; i < t; i++)
	{
		scanf("%s", T);
		scanf("%s", S);
		int amount = sol.kmp(S, T);
		cout << amount << endl;
	}

	return 0;
}
