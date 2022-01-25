#include <iostream>
using namespace std;

int main ()
{
	int d[7] = {0}, schedule[7] = {0};
	// d: 輸入之demands // schedule: 最後輸出的schedule 
	for (int i = 0; i < 7; i++)  // 輸入
		cin >> d[i];
		
	for (int i = 0; i < 7; i++)
	{
		if (d[i] > 0)  // 若所需警察數 > 0 
		{
			int policeNum = d[i];  // policeNum: 分配警察數至day(i+1) 
			for (int j = 0; j < 5; j++)   // 從d[]扣除所分配之警察數(policeNum) 
			{ 
				if (i + j > 6)  // 陣列位置為0~6，若i+j > 6，則從0開始算起
					d[i+j-7] -= policeNum;
				else
					d[i+j] -= policeNum;
			}
			schedule[i] += policeNum;  // 記下每天分配的警察數
		}
	}

	for (int i = 0; i < 6; i++)
		cout << schedule[i] << " ";
	cout << schedule[6];
	return 0;
}
