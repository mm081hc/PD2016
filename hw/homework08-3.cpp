#include <iostream>
using namespace std;

int main ()
{
	int d[7] = {0}, dMemo[7] = {0}, schedule[7] = {0};
	// d: 輸入之demands // dMemo: 與d相同，用來還原d // schedule: 所需警察數
	for (int i = 0; i < 7; i++)  // 輸入
	{
		cin >> d[i];
		dMemo[i] = d[i];
	}
		
	for (int i = 0; i < 7; i++)
	{
		for (int k = 0; k < 7; k++)
		{
			int day = i + k;  // 從第i+1天開始 
			if (i + k > 6)
				day = i + k - 7;  // 陣列位置為0~6，若i+k > 6，則從0開始算起 
			if (d[day] > 0)
			{
				int policeNum = d[day];  // policeNum: 分配警察至d[k]
				for (int j = 0; j < 5; j++)   // 從d[]扣除所分配之警察數(policeNum) 
				{ 
					if (day + j > 6)  // 陣列位置為0~6，若day+j > 6，則從0開始算起  
						d[day+j-7] -= policeNum;
					else
						d[day+j] -= policeNum;
				}
				schedule[i] += policeNum;  // 記下每天分配的警察數
			}
		}
		for (int k = 0; k < 7; k++)  // 還原d陣列中的值
			d[k] = dMemo[k];
	}

	for (int i = 0; i < 6; i++)
		cout << schedule[i] << " ";
	cout << schedule[6];

	return 0;
}
