#include <iostream>
using namespace std;

int main()
{
	int matrix[8][8] = {0}, num[6] = {0};
	// num[i]: �Ʀri�X�{�����ơC���]�Ʀr1�`�@�X�{3���A�hnum[1] = 3 
	int max = 0;  // max: �Ʀr�X�{�����Ƴ̤j�� 
	for (int i = 1; i <= 7; i++)
	{
		for (int j = 1; j <= 7; j++)
		{
			cin >> matrix[i][j];
			for (int k = 1; k <= 5; k++)
			{
				if (matrix[i][j] == k)  // �Y��J����= k(k: 1~5)�Anum[k] + 1
				{
					num[k]++;
					break;
				}	
			}
		}
	}
	for (int i = 1; i <= 5; i++)  // ����C�ӼƦr�X�{���ƪ��j�p 
	{
		if (num[i] > max)
			max = num[i];
	}
	
	int length = 0, lengthMax = 0;
	// length: �s�򪺪��� // lengthMax: �s�򪺪��׳̤j�� 
	/* �P�_�s��Ʀr���ת���k:
	�Y�۳s��Ƭ۵��Alength + 1�F�Y���۵��Alength�k�s
	�p 1 1 1 1 2�Alength��3 */
	for (int i = 1; i <= 7; i++)  // row
	{
		length = 0;
		for (int j = 1; j < 7; j++)
		{
			if (matrix[i][j] == matrix[i][j+1])
			{
				length++; 
				if (length > lengthMax)  // �p��length���P�ɻPmax����A�Ylength���j�h���N
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
	// �̫�n��XlengthMax + 1�~�O�u�������� 
	
	return 0;
}
