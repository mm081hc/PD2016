#include <iostream>
using namespace std;

int main()
{
	int n = 0, x[110] = {0};
	cin >> n;
	for (int i = 0; i <= n; i++)
	{
		cin >> x[i];
//		cout << x[i] << " ";
	}
	
	int len = 0, temp = 0, lenMax = 0, iPos = 0;
	
	for (int i = 1; i <= n; i++)
	{
		len = 0;
		temp = x[i];
		x[i] = x[0];
		
		for (int j = 1; j <= n; j++)
		{
			if (x[j] > 0)
			{
				len++;
				if (len > lenMax)
				{
					lenMax = len;
					iPos = i;
				}
//				cout << lenMax << endl;
			}
			else
			{
				len = 0;
			}
		}

		x[i] = temp;
	}
	cout << iPos << " " << lenMax;
	
	return 0;
}
