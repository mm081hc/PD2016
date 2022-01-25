#include <iostream>
#include <cstring>
#include <cmath>
#include <cctype>
#include <stdio.h> 
using namespace std;
int city(int start, int n, int m[][111], int step[], int stepCount);

int main()
{
	int n = 0, matrix[111][111] = {0};
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cin >> matrix[i][j];
		}
	}
	int step[111] = {1}, stepCount = 0;
	city(1, n, matrix, step, stepCount);

	for (int i = 0; i < n - 1; i++)
		cout << step[i] << " ";
	cout << step[n-1];
	return 0;
}

int city(int start, int n, int m[][111], int step[], int stepCount)
{
	int min = 200, minPos = 0;
	for (int i = 1; i <= n; i++)
	{	
		bool last = 0;
		for (int j = 0; j < n; j++)
		{ // 檢查是否走過 
			if (i == step[j])
			{
				last = 1;
				break;
			}
		}
		if (m[start][i] > 0 && last == 0)
		{
			if (m[start][i] < min)
			{
				min = m[start][i];
				minPos = i; 

			}
		}
	}
//	cout << minPos << endl;
	stepCount += 1;
//	cout << stepCount << endl;
	step[stepCount] = minPos;
	if (minPos != 0)
		city(minPos, n, m, step, stepCount);
}
