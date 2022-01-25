#include <iostream>
using namespace std;

int main()
{
	int n, s1, s2, s3, max = 0, maxTemp = 0, maxPos = 0;
	// max: 分數最高的值 // maxTemp: 暫存分數 // maxPos: 有max值時的座標(i) 
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
	
	for(int i = 1; i <= 9; i++)  // 尋找未畫O或X的位置(y[i]為1處) 
	{
		int x1 = 0, x2 = 0, x3 = 0;

		if (y[i] == 1)
		{
			if (n % 2 == 0)  // BetaTTT為O 
			{
				y[i] = 3;  // 將O下在y[i] 
				
				/*以下的for迴圈用來判斷一行裡的圈和空白數 
				若一行有一圈二空白，相乘值為3
				二圈一空白相乘為9，三圈相乘為27*/
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
				
				maxTemp = s1 * x1 + s2 * x2 + s3 * x3;  // 當前分數 

				if (maxTemp > max)  // 若當前計算的分數比max大，替換max  
				{
					maxPos = i;
					max = maxTemp;
				}
				
			}
			else  // BetaTTT為X 
			{
				y[i] = 2;  // 將X下在y[i] 
				
				/*以下的for迴圈用來判斷一行裡的叉和空白數 
				若一行有一叉二空白，相乘值為2 
				二叉一空白相乘為4，三叉相乘為8*/				
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
				
				maxTemp = s1 * x1 + s2 * x2 + s3 * x3;  // 當前分數 

				if (maxTemp > max)  // 若當前計算的分數比max大，替換max 
				{
					maxPos = i;
					max = maxTemp;
				}
			}
			cout << x1 << " " << x2 << " " << x3 << endl;
			cout << maxTemp << endl;
			y[i] = 1;  // 計算完分數後將y[i]改回空白的狀態 
		}
	}
 
	cout << maxPos << " " << max;
	
	return 0;
}
