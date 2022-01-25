#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

int main()
{
	int m = 0, n = 0, k = 0, d = 0;
	char b[110][110] = {0};
	cin >> n >> m >> k;
	
	char word[100] = {0};
	int x = 0, y = 0;
	int occupy = 0;
	int conflict[110][110] = {0};
	for (int i = 0; i < k; i++)
	{
		cin >> word;
		cin >> x >> y >> d;
		if (d == 2)
		{
			for (int j = 0; j < strlen(word); j++)
			{
				if (b[x][y+j] == 0)
				{
					b[x][y+j] = word[j];
					occupy++;	
				}	
				else if (b[x][y+j] != word[j])
				{
					conflict[x][y+j] = 1;
				}
			}
		}
		else
		{
			for (int j = 0; j < strlen(word); j++)
			{
				if (b[x+j][y] == 0)
				{
					b[x+j][y] = word[j];
					occupy++;	
				}	
				else if (b[x+j][y] != word[j])
				{
					conflict[x+j][y] = 1;
				}
			}			
		}
//		cout << occupy << endl;
	}
	
/*	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			cout << b[i][j] << " ";
		cout << endl;	
	}*/
	int conflictNum = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			conflictNum += conflict[i][j];
	if (conflictNum == 0)
		cout << occupy;
	else
		cout << n * m - occupy + conflictNum;
			
	return 0;
}
