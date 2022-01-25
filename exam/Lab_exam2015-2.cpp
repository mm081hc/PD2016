#include <iostream>
using namespace std;

int main()
{
	int B = 0, n = 0, q[110] = {0}, p[110] = {0}, q2[110] = {0}, price = 0, quan = 0;
	cin >> n >> B;
	for (int i = 0; i < n; i++)
		cin >> q[i];

	for (int i = 0; i < n; i++)
		cin >> p[i];
	
	quan = q[0] + 1;
	price = q[0] * p[0];
	bool flag = 1;
	for (int i = 0; i < n; i++)
	{
		if (B <= q[0] * p[0])
		{
			quan = B / p[0];
			price = quan * p[0];
			break;
		}
		else if (quan > q[n-1])
		{
			quan = q[n-1];
			break;
		}
		else
		{
			while (quan > q[i] && quan <= q[i+1])
			{
				price += p[i+1];
				if (price > B)
				{
					quan = quan - 1;
					price = price - p[i+1];
					flag = 0;
					break;	
				}
				else if (quan == q[n-1])
					break;

				quan++;
//				cout << quan << " " << price << endl;
			}
		}
		if (flag == 0)
			break;
	}

	cout << quan << " " << price;

	return 0;
}
