#include <iostream>
using namespace std;

int x1Function(int [], int n, int i);  // ��J�ѽL��m�Bn�ȡB���i�ȡA��Xx1
int x2Function(int [], int n, int i);  // ��J�ѽL��m�Bn�ȡB���i�ȡA��Xx2 
int x3Function(int [], int n, int i); // ��J�ѽL��m�Bn�ȡB���i�ȡA��Xx3

int main()
{
	int n = 0, s1 = 0, s2 = 0, s3 = 0, x1 = 0, x2 = 0, x3 = 0;
	int max = 0, maxTemp = 0, maxPos = 0;
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
		if (y[i] == 1)
		{
				x1 = x1Function(y, n, i);
				x2 = x2Function(y, n, i);
				x3 = x3Function(y, n, i);
				maxTemp = s1 * x1 + s2 * x2 + s3 * x3;  // ��e����
				if (maxTemp > max)  // �Y��e�p�⪺���Ƥ�max�j�A����max  
				{
					maxPos = i;
					max = maxTemp;
				}
		}
	}
 
	cout << maxPos << " " << max;
	
	return 0;
}

/* �p��x1, x2, x3����k:
	O:
	�Y�@�榳�@�e�G�ťաA�ۭ��Ȭ�3 
	�G�e�@�ťլۭ���9�A�T�e�ۭ���27	
	X:
	�Y�@�榳�@�e�G�ťաA�ۭ��Ȭ�2 
	�G�e�@�ťլۭ���4�A�T�e�ۭ���8*/

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
