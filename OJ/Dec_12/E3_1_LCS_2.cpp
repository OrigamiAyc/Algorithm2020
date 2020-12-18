#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int get_max_length(const string &x, const string &y, vector<vector<int>> &dp)
{
	int xlen = x.size();
	int ylen = y.size();

	dp[0][0] = x[0] == y[0] ? 1 : 0;

	for (int i = 1; i < xlen; i++)
	{
		// 当前位置取值只可能是其上方的值或者当前位置的值
		dp[i][0] = max(dp[i - 1][0], x[i] == y[0] ? 1 : 0);
		//dp[i][0] = dp[i-1][0] == 1 ? 1 : （x[i] == y[0] ？ 1 ： 0）；
	}

	for (int j = 1; j < ylen; j++)
	{
		dp[0][j] = max(dp[0][j - 1], (x[0] == y[j] ? 1 : 0));
	}

	for (int i = 1; i < xlen; i++)
	{
		for (int j = 1; j < ylen; j++)
		{
			dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
		}
	}

	return dp[xlen - 1][ylen - 1];
}

void max_len_str(const string &x, const string &y, string &z, vector<vector<int>> &dp)
{
	int xlen = x.size() - 1;
	int ylen = y.size() - 1;
	int index = get_max_length(x, y, dp) - 1;
	while (index)
	{
		if (ylen > 0 && dp[xlen][ylen] == dp[xlen][ylen - 1])
		{
			ylen--;
		}
		else if (xlen > 0 && dp[xlen][ylen] == dp[xlen - 1][ylen])
		{
			xlen--;
		}
		else
		{
			// 从当前位置，向左上方遍历
			z.push_back(x[xlen]); // 逆序存储最长公共子序列
			index--;
			xlen--;
			ylen--;
		}
	}
}

int main()
{
	string str_a;
	string str_b;
	cin >> str_a;
	cin >> str_b;

	int alen = str_a.size();
	int blen = str_b.size();
	vector<vector<int>> dp(alen, vector<int>(blen, 0));

	string result_str;
	max_len_str(str_a, str_b, result_str, dp);

	if (0 == result_str.size())
	{
		return -1;
	}
	else
	{
		reverse(result_str.begin(), result_str.end());
		cout << result_str << endl;
	}

	return 0;
}
