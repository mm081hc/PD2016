#include <iostream>
#include <algorithm>  // sort定義於此標頭檔 
using namespace std;

int main()
{
	int n, dia, sum[4] = {0}, min = 0;  // dia = number of diamonds；sum為4人各自的寶物數，一開始皆為0 
	cin >> n;
	
	for (int j = 1; j <= n; j++)  // j: 第j次輸入
	{
		cin >> dia;  // 當輸入次數小於n，輸入dia
		for (int i = 0; i < 4; i++)
		{
			if (sum[i] < sum[min])
				min = i;  // 若sum[i]比當前最小值小，更新最小值的註標
				/* 因i從0開始增加，故即使後面有人寶物數與前面的人相同，
				條件式不會成立，不會更改最小值註標。即是不必判斷寶物數相同的狀況 */
		}
		sum[min] = sum[min] + dia;  // 將寶物分配給寶物數最少的人 
	}
	
	sort (sum, sum+4);  // 依小到大排序四人的寶物數
	cout << sum[0] << " " << sum[1] << " " << sum[2] << " " << sum[3];
	
	return 0;
}
