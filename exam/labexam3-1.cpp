#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int n = 0, x[1010] = {0}, total = 0, totalAbs = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x[i];
		total += x[i];
		totalAbs += abs(x[i]);
	}	
	
	int k = -1, sum = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		if (2 * sum == total)
		{
			k = i;
			break;
		}
		sum += x[i];
	//	cout << i << " " << sum << endl;
	}
	
	if (k == -1)
		cout << k + 1 << " " << totalAbs;
	else
		cout << k + 1 << " " << total;	
	return 0;
}
