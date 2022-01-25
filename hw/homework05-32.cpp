#include <iostream>
using namespace std;

int main()
{
	int n = 0, p[150] = {0}, s[110][110] = {0};
	int min = 0, ijSum = 0, sum = 0;
	// min: setup time總和之最小值 // ijSum: i+j // sum: 初始的setup time總和 
	int iPos = 0, jPos = 0, pTime = 0, sTime = 0;
	// iPos, jPos: min時的i, j值 // pTime: sum of processing times // sTime: sum of setup times
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		cin >> p[i]; 
		pTime += p[i];  // 計算processing times的總和 
	}
	for (int i = 1; i <= n; i++) 
		for(int j = 1; j <= n; j++) 
			cin >> s[i][j]; 
	
	for (int i = 1; i < n; i++)
		sum += s[i][i+1];  // 計算初始的setup time總和
	min = sum;  // 令初始setup time總和為當前最小值
	
	for (int i = 1; i < n; i++)  // 任選兩位置互換 
	{
		for (int j = i + 1; j <= n; j++)
		{
			/*計算setup time:
			交換過位置的setup time和原本的相比，最多相差4個數
			即s[i-1][i], s[i][i+1], s[j-1][j], s[j][j+1]
			故扣除初始的這四個值，再加上交換後的這四個值，即為當前的setup time*/
			if (j == i + 1)  // ij相鄰 
			sTime = sum - s[i-1][i] - s[i][j] - s[j][j+1]
						+ s[i-1][j] + s[j][i] + s[i][j+1];
						
			else  // 其餘狀況 
			sTime = sum - s[i-1][i] - s[i][i+1] - s[j-1][j] - s[j][j+1]
						+ s[i-1][j] + s[j][i+1] + s[j-1][i] + s[i][j+1];

			if (sTime < min || (sTime == min && i + j <= ijSum))
			{
				// 若
				min = sTime;  // 更換min, ijSum, iPos, jPos 
				ijSum = i + j;
				iPos = i;
				jPos = j;
			}
//			cout << sTime << " ";
		}
//		cout << pTime << " " << pTime + min << " " << min << endl;
	}
	
	for (int i = 1; i <= n; i++)  // 輸出順序 
	{
		if (i == iPos)  // 輸到第i個位置，改為j 
			cout << jPos << " ";
		else if (i == jPos)  // 輸到第j個位置，改為i 
			cout << iPos << " ";
		else
			cout << i << " ";
	}
	cout << pTime + min;  // 輸出時間總和 
	
	return 0;
}
