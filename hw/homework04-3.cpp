#include <iostream>
using namespace std;

int main()
{
	int n, s1, s2, s3, max = 0, maxTemp = 0, maxPos = 0;
	// max: ���Ƴ̰����� // maxTemp: �Ȧs���� // maxPos: ��max�Ȯɪ��y��(i) 
	int y[10];  
	// y[i]�����ѽL�W����m ex. y[1]���Ĥ@�Ӧ�m 
	for (int i = 1; i <= 10; i++)  // �N�C�Ӧ�m����(y[i])��l�Ƭ�1 
		y[i] = 1;
	
	cin >> n >> s1 >> s2 >> s3;

	for (int i = 1, j = 1; i <= n; i++)  // ��J�ѽL��m 
	{
		cin >> j;
		
		if (i % 2 == 1)  // �H3�N��"O" 
			y[j] = 3;
		else
			y[j] = 2;  // �H2�N��"X" 
	}
	
	for(int i = 1; i <= 9; i++)  // �M�䥼�eO��X����m(y[i]��1�B) 
	{
		int x1 = 0, x2 = 0, x3 = 0;

		if (y[i] == 1)
		{
			if (n % 2 == 0)  // BetaTTT��O 
			{
				y[i] = 3;  // �NO�U�by[i] 
				
				/*�H�U��for�j��ΨӧP�_�@��̪���M�ťռ� 
				�Y�@�榳�@��G�ťաA�ۭ��Ȭ�3
				�G��@�ťլۭ���9�A�T��ۭ���27*/
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
				
				maxTemp = s1 * x1 + s2 * x2 + s3 * x3;  // ��e���� 

				if (maxTemp > max)  // �Y��e�p�⪺���Ƥ�max�j�A����max  
				{
					maxPos = i;
					max = maxTemp;
				}
				
			}
			else  // BetaTTT��X 
			{
				y[i] = 2;  // �NX�U�by[i] 
				
				/*�H�U��for�j��ΨӧP�_�@��̪��e�M�ťռ� 
				�Y�@�榳�@�e�G�ťաA�ۭ��Ȭ�2 
				�G�e�@�ťլۭ���4�A�T�e�ۭ���8*/				
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
				
				maxTemp = s1 * x1 + s2 * x2 + s3 * x3;  // ��e���� 

				if (maxTemp > max)  // �Y��e�p�⪺���Ƥ�max�j�A����max 
				{
					maxPos = i;
					max = maxTemp;
				}
			}
			cout << x1 << " " << x2 << " " << x3 << endl;
			cout << maxTemp << endl;
			y[i] = 1;  // �p�⧹���ƫ�Ny[i]��^�ťժ����A 
		}
	}
 
	cout << maxPos << " " << max;
	
	return 0;
}
