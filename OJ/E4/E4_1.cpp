#include <iostream>
#include <cstring>
using namespace std;

bool village[1000001];

int main(int argc, char const *argv[])
{
	int n, r;
	cin >> n >> r;
	memset(village, 0, 1000001 * sizeof(bool));
	int temp;
	for (size_t i = 0; i < n; i++)
	{
		cin >> temp;
		village[temp] = true;
	}
	int amount = 0;
	int count = 0;
	while (count < 1000001)
	{
		if (village[count])
		{
			amount++;
			count += r;				// Max pos that can cover this village
			while (!village[count]) // to find a village to build station
			{
				count--;
			}
			count += r; // r pos after the station can be covered
		}
		count++;
	}
	cout << amount << endl;
	return 0;
}
