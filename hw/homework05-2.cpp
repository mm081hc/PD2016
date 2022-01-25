#include <iostream>
using namespace std;

int x1Function(int [], int n, int i);  // 輸入棋盤位置、n值、當時i值，算出x1
int x2Function(int [], int n, int i);  // 輸入棋盤位置、n值、當時i值，算出x2 
int x3Function(int [], int n, int i); // 輸入棋盤位置、n值、當時i值，算出x3

int main()
{
	int n = 0, s1 = 0, s2 = 0, s3 = 0, x1 = 0, x2 = 0, x3 = 0;
	int max = 0, maxTemp = 0, maxPos = 0;
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
		if (y[i] == 1)
		{
				x1 = x1Function(y, n, i);
				x2 = x2Function(y, n, i);
				x3 = x3Function(y, n, i);
				maxTemp = s1 * x1 + s2 * x2 + s3 * x3;  // 當前分數
				if (maxTemp > max)  // 若當前計算的分數比max大，替換max  
				{
					maxPos = i;
					max = maxTemp;
				}
		}
	}
 
	cout << maxPos << " " << max;
	
	return 0;
}

/* 計算x1, x2, x3的方法:
	O:
	若一行有一叉二空白，相乘值為3 
	二叉一空白相乘為9，三叉相乘為27	
	X:
	若一行有一叉二空白，相乘值為2 
	二叉一空白相乘為4，三叉相乘為8*/

int x1Function(int a[], int n, int i)
{
	int x = 0;
	if (n % 2 == 0)  // O 
	{
		a[i] = 3; 
		for (int k = 1; k <= 7; k += 3)  // row
			if (a[k] * a[k+1] * a[k+2] == 3)
				x++;
		for (int k = 1; k <= 3; k++)  // column		
			if (a[k] * a[k+3] * a[k+6] == 3)
				x++;
		if (a[1] * a[5] * a[9] == 3)  // diagonal
				x++;
		if (a[3] * a[5] * a[7] == 3)  // diagonal
				x++;
	}
	else  // X
	{
		a[i] = 2;
		for (int k = 1; k <= 7; k += 3)  // row
			if (a[k] * a[k+1] * a[k+2] == 2)
				x++;
		for (int k = 1; k <= 3; k++)  // column		
			if (a[k] * a[k+3] * a[k+6] == 2)
				x++;
		if (a[1] * a[5] * a[9] == 2)  // diagonal
				x++;
		if (a[3] * a[5] * a[7] == 2)  // diagonal
				x++;		
	}
	a[i] = 1;
	return x;
}

int x2Function(int a[], int n, int i)
{
	int x = 0;
	if (n % 2 == 0)  // O
	{
		a[i] = 3;
		for (int k = 1; k <= 7; k += 3)  // row
			if (a[k] * a[k+1] * a[k+2] == 9)
				x++;
		for (int k = 1; k <= 3; k++)  // column		
			if (a[k] * a[k+3] * a[k+6] == 9)
				x++;
		if (a[1] * a[5] * a[9] == 9)  // diagonal
				x++;
		if (a[3] * a[5] * a[7] == 9)  // diagonal
				x++;
	}
	else  // X
	{
		a[i] = 2;
		for (int k = 1; k <= 7; k += 3)  // row
			if (a[k] * a[k+1] * a[k+2] == 4)
				x++;
		for (int k = 1; k <= 3; k++)  // column		
			if (a[k] * a[k+3] * a[k+6] == 4)
				x++;
		if (a[1] * a[5] * a[9] == 4)  // diagonal
				x++;
		if (a[3] * a[5] * a[7] == 4)  // diagonal
				x++;		
	}
	a[i] = 1;
	return x;
}

int x3Function(int a[], int n, int i)
{
	int x = 0;
	if (n % 2 == 0)  // O
	{
		a[i] = 3;
		for (int k = 1; k <= 7; k += 3)  // row
			if (a[k] * a[k+1] * a[k+2] == 27)
				x++;
		for (int k = 1; k <= 3; k++)  // column		
			if (a[k] * a[k+3] * a[k+6] == 27)
				x++;
		if (a[1] * a[5] * a[9] == 27)  // diagonal
				x++;
		if (a[3] * a[5] * a[7] == 27)  // diagonal
				x++;
	}
	else  // X
	{
		a[i] = 2;		
		for (int k = 1; k <= 7; k += 3)  // row
			if (a[k] * a[k+1] * a[k+2] == 8)
				x++;
		for (int k = 1; k <= 3; k++)  // column		
			if (a[k] * a[k+3] * a[k+6] == 8)
				x++;
		if (a[1] * a[5] * a[9] == 8)  // diagonal
				x++;
		if (a[3] * a[5] * a[7] == 8)  // diagonal
				x++;		
	}
	a[i] = 1;
	return x;
}
