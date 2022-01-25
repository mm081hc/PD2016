#include <iostream>
using namespace std;

void swap (int [], int, int);  // swap(): 輸入陣列位置、要交換的座標，交換位置 

int main()
{
	int n = 0, p[150] = {0}, s[110][110] = {0}; 
	int order[101] = {0}, min = 0, minFin = 0, indexSum = 0;
	// order: 當前順序 // min: setup time總和之最小值
	// minFin: 最終的setup time總和最小值 // indexSum: sum of switching indices
	int pTime = 0, indexMin = 0, iPos = 0, jPos = 0;
	// pTime: sum of processing times // indexMin: 紀錄switching indices中較小的數 
	// iPos, jPos: 紀錄min時的i, j 
	
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		order[i] = i;  // 初始順序(1, 2,...,n) 
		cin >> p[i];
		pTime += p[i];  // 加總processing times 
	}
	for (int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			cin >> s[i][j];
	
	for (int i = 1; i < n; i++)
		min += s[order[i]][order[i+1]];  // 計算初始的setup time總和，令其為最小值min
	minFin = min; // 將此min設為最終的最小值 
	
	bool exist = 1;  // exist: 當存在最小值時，其值為1 
	while (exist == 1)
	{
		for (int i = 1; i < n; i++)  // 取任意兩數互換 
		{
			for (int j = i + 1; j <= n; j++)
			{ 
				swap(order, i, j);  // 兩數互換 
				int sTime = 0;  // sTime: sum of setup time
				for (int k = 1; k < n; k++)
				{
					sTime += s[order[k]][order[k+1]];  // 計算當前setup time
					if (sTime > min)  // 若已超過當前最小值，跳出迴圈 
						break;
				}
				if (sTime < min || (sTime == min && order[i] + order[j] < indexSum))
				{
					// 若當前setup time比最小值小，替換最小值
					// 若等於最小值則檢查switching indices的和是否較小 
					min = sTime;  // 更換min, iPos, jPos, indexSum, indexMin 
					iPos = i;
					jPos = j;
					indexSum = order[i] + order[j];
					if (order[i] < order[j])  // 將較小的switching indices值輸入indexMin 
						indexMin = order[i];
					else
						indexMin = order[j];
				}
				else if (sTime == min && order[i] + order[j] == indexSum
						&& (order[i] < indexMin || order[j] < indexMin))
				{
					// 若當前setup time等於min，且indexSum相同，
					// 則檢查switching indices任一是否比indexMin小，若有則替換indices
					min = sTime;
					iPos = i;
					jPos = j;
					indexSum = order[i] + order[j];					
					if (order[i] < order[j])
						indexMin = order[i];
					else
						indexMin = order[j];	
				}
				swap (order, i, j);  // 兩數換回原位置
			}
		}
		if (minFin == min)  // 若互換後最終最小值仍未改變，將exist設為0，跳出迴圈
			exist = 0;
		else  // 若minFin改變，換至目前min時的狀態，並再次檢查是否有更小的 
		{
			exist = 1;
			minFin = min;
			swap(order, iPos, jPos); 
		}
	}
	
	for (int i = 1; i <= n; i++)
		cout << order[i] << " ";
	cout << pTime + minFin;  // 輸出processing time + setup time
	
	return 0;
}

void swap (int x[], int a, int b)
{
	int temp = 0;
	temp = x[a];
	x[a] = x[b];
	x[b] = temp;
}
