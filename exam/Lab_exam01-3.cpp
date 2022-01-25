#include <iostream>
using namespace std;

int main()
{
	int n = 0, iPos = 0;
	double s[210][10] = {0};
	double pro = 0, max = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cin >> s[i][j];
		}
		s[i][8]++;
	}
	
	bool same = 1;
	for (int i = 0; i < n; i++)
	{
		if (s[i][0] == -1)
			continue;

		for (int j = i + 1; j < n; j++)
		{
			same = 1;
			for (int k = 0; k < 5; k++)
			{
				if (s[i][k] != s[j][k])
				{
					same = 0;
					break;
				}
			}
			if (same == 1)
			{
				s[j][0] = -1;
				s[i][7] += s[j][7];
				s[i][8]++;
			}
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		if (s[i][0] == -1)
			continue;
				
		pro = s[i][7] / s[i][8];
		if (pro > max)
		{
			max = pro;
			iPos = i;
		}
	}

	for (int i = 0; i <= 6; i++)
	{
		if (s[iPos][i] == 1)
			cout << i + 1 << " ";
	}
	cout << s[iPos][7] << " " << s[iPos][8] - s[iPos][7];
	return 0;
}
