#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	int n = 0, k = 0, x[200] = {0};
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		cin >> x[i];
	if (k > n)
		cout << -1;
	else
	{
		sort (x, x+n);
		reverse (x, x+n);
		cout << x[k-1];
	}

	return 0;
}
