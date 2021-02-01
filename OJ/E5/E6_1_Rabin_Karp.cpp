#include <iostream>
#include <cstdio>
using namespace std;

#define d 26

/**
 * S  -> Search Sequence
 * T  -> Target Sequence
 * q  -> A prime number
 **/
void search(char *S, char *T, int q)
{
	int M = strlen(S);
	int N = strlen(T);
	int i, j;
	int SHashValue = 0; // hash value for Search Sequence
	int THashValue = 0; // hash value for Target Sequence
	int h = 1;			// h 的计算公式：pow(d, M-1) % q

	int count = 0;

	//计算h
	for (i = 0; i < M - 1; i++)
		h = (h * d) % q;

	// Calculate the hash value of Search Sequence
	for (i = 0; i < M; i++)
	{
		SHashValue = (d * SHashValue + S[i]) % q;
		THashValue = (d * THashValue + T[i]) % q;
	}

	// Slide the pattern over text one by one
	for (i = 0; i <= N - M; i++)
	{
		// Chaeck the hash values of current T and S
		// If the hash values match then only check for characters on by one
		if (SHashValue == THashValue)
		{
			/* Check for characters one by one */
			for (j = 0; j < M; j++)
			{
				if (S[i + j] != T[j])
					break;
			}
			if (j == M)
			{ // if SHashValue == THashValue and S[0...M-1] = T[i, i+1, ...i+M-1]
				count++;
			}
		}

		// Calulate hash value for next text: Remove leading digit,
		// add trailing digit
		if (i < N - M)
		{
			THashValue = (d * (THashValue - T[i] * h) + T[i + M]) % q;
			// We might get negative value of THashValue, converting it to positive
			if (THashValue < 0)
				THashValue = (THashValue + q);
		}
	}
	cout << count << endl;
}

int main(int argc, char const *argv[])
{
	int k;
	cin >> k;
	char *S, *T;
	for (size_t i = 0; i < k; i++)
	{
		scanf("%s", T);
		scanf("%s", S);
		search(S, T, 1);
	}

	return 0;
}
