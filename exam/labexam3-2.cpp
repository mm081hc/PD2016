#include <iostream>
using namespace std;

int main()
{
	int m = 0, n = 0, b[110][110] = {0};
	cin >> n >> m;
	int row = 0, column = 0, noborder = 0;
	for (int i = 0; i < m; i++)
	{
		cin >> row >> column;
		b[row][column] = 1;
		if (row != 1 && column != 1)
			noborder++;
	}
/*	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
			cout << b[i][j] << " ";
		cout << endl;	
	}
*/	
	int isolate = 0, noisolate = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (b[i][j] == 1)
			{// coin
				if(b[i-1][j] == 1 || b[i+1][j] == 1 || b[i][j-1] == 1 || b[i][j+1] == 1)
				{
					if (i != 1 && j != 1 && i != n && j != n)
						noisolate++;
				}
				else
				{
					isolate++;
				}
			}
		}
	}
	cout << isolate << " " << noisolate;
	return 0;
}
