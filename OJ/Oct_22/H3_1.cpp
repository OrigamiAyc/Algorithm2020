#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main(int argc, char const *argv[])
{
	int n, k;
	cin >> n >> k;
	int audience[n];
	for (size_t i = 0; i < n; i++)
	{
		cin >> audience[i];
	}
	sort(audience, audience + n);
	cout << audience[k - 1] << endl;
	return 0;
}
