#include <iostream>
#include <cstring>
using namespace std;

int RabinKarp(string S, string T)
{
	int Snum = 0;
	int Tnum = 0;
	int count = 0;
	int Slen = S.length();
	int Tlen = T.length();

	for (size_t i = 0; i < Tlen; i++)
	{
		Snum += (S[i] - 'a');
		Tnum += (T[i] - 'a');
	}

	// if the num do not equal, there is no chance that two strings match
	for (size_t i = 0; i < (Slen - Tlen); i++)
	{
		if (Snum != Tnum)
		{
			Snum += (S[i + Tlen] - S[i]);
			continue;
		}
		else
		{
			int ifMatch = S.compare(i, Tlen, T);
			count += ((ifMatch == 0) ? 1 : 0);
			Snum += (S[i + Tlen] - S[i]);
		}
	}
	return count;
}

int main(int argc, char const *argv[])
{
	int t;
	cin >> t;
	string S, T;
	for (size_t i = 0; i < t; i++)
	{
		cin >> T >> S;
		int num = RabinKarp(S, T);
		cout << num << endl;
	}

	return 0;
}
