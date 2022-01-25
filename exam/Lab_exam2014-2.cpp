#include <iostream>
using namespace std;

int main()
{
	int matrix[8][8] = {0}, num[6] = {0};
	// num[i]: 计i瞷Ω计安砞计1羆瞷3Ω玥num[1] = 3 
	int max = 0;  // max: 计瞷Ω计程 
	for (int i = 1; i <= 7; i++)
	{
		for (int j = 1; j <= 7; j++)
		{
			cin >> matrix[i][j];
			for (int k = 1; k <= 5; k++)
			{
				if (matrix[i][j] == k)  // 璝块计= k(k: 1~5)num[k] + 1
				{
					num[k]++;
					break;
				}	
			}
		}
	}
	for (int i = 1; i <= 5; i++)  // ゑ耕–计瞷Ω计 
	{
		if (num[i] > max)
			max = num[i];
	}
	
	int length = 0, lengthMax = 0;
	// length: 硈尿 // lengthMax: 硈尿程 
	/* 耞硈尿计よ猭:
	璝硈ㄢ计单length + 1璝ぃ单length耴箂
	 1 1 1 1 2length3 */
	for (int i = 1; i <= 7; i++)  // row
	{
		length = 0;
		for (int j = 1; j < 7; j++)
		{
			if (matrix[i][j] == matrix[i][j+1])
			{
				length++; 
				if (length > lengthMax)  // 璸衡length籔maxゑ耕璝length耕玥
					lengthMax = length;
			}
			else
				length = 0;
		}
	}
	

	for (int i = 1; i <= 7; i++)  // column
	{
		length = 0;
		for (int j = 1; j < 7; j++)
		{
			if (matrix[j][i] == matrix[j+1][i])
			{
				length++;
				if (length > lengthMax)
					lengthMax = length;
			}
			else
				length = 0;
		}
	}
	
	cout << max << " " << lengthMax + 1 << endl;
	// 程璶块lengthMax + 1琌痷タ 
	
	return 0;
}
