#include <iostream>
using namespace std;

int main()
{
	int n, s1, s2, s3, temp = 0;
	// max: ��U���Ƴ̤j�� // maxTemp: �Ȧs����
	int min = 900, minPos = 0;  // min: ���������ƪ��̤p�ȡA��l�ȬO�H�K�]��XD // minPos: �̤p�Ȯɪ��y�� 
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
//	cout << y[1] << " " << y[2] << " " << y[3] << endl;
//	cout << y[4] << " " << y[5] << " " << y[6] << endl;
//	cout << y[7] << " " << y[8] << " " << y[9] << endl << endl;
		
	for(int i = 1; i <= 9; i++)  // �M�䥼�eO��X����m(y[i]��1�B) 
	{
		int max = 0; 
		
		if (y[i] == 1)
		{
			if (n % 2 == 0)  // BetaTTT: O
			{
				y[i] = 3;  // �NO�U�by[i] 
				
				for (int j = 1; j <= 9; j++)  // ��ⱡ�p 
				{
					if (y[j] == 1)
					{
						int x1 = 0, x2 = 0, x3 = 0;
						y[j] = 2; //  ���NX�U�by[j] 

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
				
						temp = s1 * x1 + s2 * x2 + s3 * x3;  // ����e���� 

						if (temp > max)  // �Y��e�p�⪺���Ƥ�max�j�A����max 
							max = temp;

						y[j] = 1;
					}
				}
				if (max < min)  //  ���i���P�ɡA��⪺���Ƴ̤j�Ȫ��j�p(max)�A����̤p�� 
				{
					minPos = i; 
					min = max;
				}
			}
			
			else  // BetaTTT: X
			{
				y[i] = 2;  // �NX�U�by[i] 
				
				for (int j = 1; j <= 9; j++)
				{
					if (y[j] == 1)
					{
						int x1 = 0, x2 = 0, x3 = 0;
						y[j] = 3; // ���: O
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
				
						temp = s1 * x1 + s2 * x2 + s3 * x3;  // ����e���� 
					//	cout << x1 << " " << x2 << " " << x3 << endl;
					//	cout << temp << " ";
						if (temp > max)  // �Y��e�p�⪺���Ƥ�max�j�A����max 
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
			y[i] = 1;  // �p�⧹���ƫ�Ny[i]��^�ťժ����A
		}
		// cout << i << " " << minPos << " " << min << " " << max << endl;
	}
	cout << minPos << " " << min;
	
	return 0;
}
