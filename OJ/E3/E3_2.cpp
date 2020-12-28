#include <iostream>
#include <vector>
using namespace std;

int **DPMatrix;
int **DPStore;

int main(int argc, char const *argv[])
{
	int n;
	cin >> n;
	DPMatrix = new int *[n + 1];
	DPStore = new int *[n + 1];
	for (size_t i = 0; i <= n; i++)
	{
		DPMatrix[i] = new int[n + 1];
		DPMatrix[i][i] = 0;
		DPStore[i] = new int[n + 1];
		DPStore[i][i] = 0;
	}

	int toMerge[220];
	for (size_t i = 1; i <= n; i++)
	{
		cin >> toMerge[i];
	}

	for (size_t l = 2; l <= n; l++)
	{
		for (size_t i = 1; i <= n-l+1; i++)
		{
			int j = i + l - 1;
			int mergeCost = 0;
			for (size_t t = i; t <= j; t++)
			{
				mergeCost += toMerge[t];
			}
			DPMatrix[i][j] = DPMatrix[i + 1][j];
			DPMatrix[i][j] = DPMatrix[i + 1][j] + mergeCost;
			DPStore[i][j] = i;
			for (size_t k = i+1; k < j; k++)
			{
				int t = DPMatrix[i][k] + DPMatrix[k + 1][j] + mergeCost;
				if (t < DPMatrix[i][j])
				{
					DPMatrix[i][j] = t;
					DPStore[i][j] = k;
				}
			}
		}
	}
	cout << DPMatrix[1][n] << endl;
	return 0;
}
