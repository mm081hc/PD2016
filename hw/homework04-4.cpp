#include <iostream>
using namespace std;

int main()
{
	int n, s1, s2, s3, temp = 0;
	// max: 當下分數最大值 // maxTemp: 暫存分數
	int min = 900, minPos = 0;  // min: 紀錄對手分數的最小值，初始值是隨便設的XD // minPos: 最小值時的座標 
	int y[10];  
	// y[i]對應棋盤上的位置 ex. y[1]為第一個位置 
	for (int i = 1; i <= 10; i++)  // 將每個位置的值(y[i])初始化為1 
		y[i] = 1;
	
	cin >> n >> s1 >> s2 >> s3;

	for (int i = 1, j = 1; i <= n; i++)  // 輸入棋盤位置 
	{
		cin >> j;	
		if (i % 2 == 1)  // 以3代表"O" 
			y[j] = 3;
		else
			y[j] = 2;  // 以2代表"X" 
	}
//	cout << y[1] << " " << y[2] << " " << y[3] << endl;
//	cout << y[4] << " " << y[5] << " " << y[6] << endl;
//	cout << y[7] << " " << y[8] << " " << y[9] << endl << endl;
		
	for(int i = 1; i <= 9; i++)  // 尋找未畫O或X的位置(y[i]為1處) 
	{
		int max = 0; 
		
		if (y[i] == 1)
		{
			if (n % 2 == 0)  // BetaTTT: O
			{
				y[i] = 3;  // 將O下在y[i] 
				
				for (int j = 1; j <= 9; j++)  // 對手情況 
				{
					if (y[j] == 1)
					{
						int x1 = 0, x2 = 0, x3 = 0;
						y[j] = 2; //  對手將X下在y[j] 

						for (int k = 1; k <= 7; k += 3)  // row 
						{
							if (y[k] * y[k+1] * y[k+2] == 2)
								x1++;
							else if (y[k] * y[k+1] * y[k+2] == 4)
								x2++;
							else if (y[k] * y[k+1] * y[k+2] == 8)
								x3++;										
						}
				
						for (int k = 1; k <= 3; k++)  // column
						{
							if (y[k] * y[k+3] * y[k+6] == 2)
								x1++;
							else if (y[k] * y[k+3] * y[k+6] == 4)
								x2++;
							else if (y[k] * y[k+3] * y[k+6] == 8)
								x3++;						
						}
				
						if (y[1] * y[5] * y[9] == 2)  // diagonal
							x1++;
						else if (y[1] * y[5] * y[9] == 4)
							x2++;
						else if (y[1] * y[5] * y[9] == 8)
							x3++;
				
						if (y[3] * y[5] * y[7] == 2)  // diagonal
							x1++;
						else if (y[3] * y[5] * y[7] == 4)
							x2++;
						else if (y[3] * y[5] * y[7] == 8)
							x3++;				
				
						temp = s1 * x1 + s2 * x2 + s3 * x3;  // 對手當前分數 

						if (temp > max)  // 若當前計算的分數比max大，替換max 
							max = temp;

						y[j] = 1;
					}
				}
				if (max < min)  //  比較i不同時，對手的分數最大值的大小(max)，取其最小的 
				{
					minPos = i; 
					min = max;
				}
			}
			
			else  // BetaTTT: X
			{
				y[i] = 2;  // 將X下在y[i] 
				
				for (int j = 1; j <= 9; j++)
				{
					if (y[j] == 1)
					{
						int x1 = 0, x2 = 0, x3 = 0;
						y[j] = 3; // 對手: O
					//	cout << y[1] << " " << y[2] << " " << y[3] << endl;
					//	cout << y[4] << " " << y[5] << " " << y[6] << endl;
					//	cout << y[7] << " " << y[8] << " " << y[9] << endl;
												
						for (int k = 1; k <= 7; k += 3)  // row 
						{
							if (y[k] * y[k+1] * y[k+2] == 3)
								x1++;
							else if (y[k] * y[k+1] * y[k+2] == 9)
								x2++;
							else if (y[k] * y[k+1] * y[k+2] == 27)
								x3++;										
						}
				
						for (int k = 1; k <= 3; k++)  // column
						{
							if (y[k] * y[k+3] * y[k+6] == 3)
								x1++;
							else if (y[k] * y[k+3] * y[k+6] == 9)
								x2++;
							else if (y[k] * y[k+3] * y[k+6] == 27)
								x3++;						
						}
				
						if (y[1] * y[5] * y[9] == 3)  // diagonal
							x1++;
						else if (y[1] * y[5] * y[9] == 9)
							x2++;
						else if (y[1] * y[5] * y[9] == 27)
							x3++;
				
						if (y[3] * y[5] * y[7] == 3)  // diagonal
							x1++;
						else if (y[3] * y[5] * y[7] == 9)
							x2++;
						else if (y[3] * y[5] * y[7] == 27)
							x3++;				
				
						temp = s1 * x1 + s2 * x2 + s3 * x3;  // 對手當前分數 
					//	cout << x1 << " " << x2 << " " << x3 << endl;
					//	cout << temp << " ";
						if (temp > max)  // 若當前計算的分數比max大，替換max 
							max = temp;

						y[j] = 1;
					//	cout << max << endl << endl;
					}
				}
				if (max < min)   
				{
					minPos = i;
					min = max;
				}
			}	
			y[i] = 1;  // 計算完分數後將y[i]改回空白的狀態
		}
		// cout << i << " " << minPos << " " << min << " " << max << endl;
	}
	cout << minPos << " " << min;
	
	return 0;
}
