#include <iostream>
using namespace std;

void station(int [][60], int [], int, int, int);
// station: ��Jadjacency matrix, station ID�}�C, x(��l�Ȭ�0), n, k�A��i��F����   

int main()
{
	int n = 0, k = 0, a[60] = {0}, s[60][60] = {0}, iMax = 0;
	// a: station ID�A�Yi���i��F�����A�ha[i] = 1 // s: adjacency matrix 
	for (int i = 1; i < 12; i++)  // �غcadjacency matrix 
	{
		s[i][i+1] = 1;
		s[13-i][12-i] = 1;
	}
	for (int i = 1; i < 14; i++)
	{
		s[12+i][13+i] = 1;
		s[27-i][26-i] = 1;
	}
	for (int i = 1; i < 24; i++)
	{
		s[26+i][27+i] = 1;
		s[51-i][50-i] = 1;
	}
	s[51][52] = s[52][53] = s[53][52] = s[52][51] = s[32][51] = s[51][32] = 1;
	s[4][29] = s[29][4] = s[4][28] = s[28][4] = 1;
	s[6][18] = s[18][6] = s[6][19] = s[19][6] = 1;
	s[9][40] = s[40][9] = s[9][41] = s[41][9] = 1;
	s[14][46] = s[46][14] = s[14][47] = s[47][14] = 1;
	s[22][35] = s[35][22] = s[22][36] = s[36][22] = 1;
	s[27][50] = s[50][27] = 1;
	s[18][19] = s[19][18] = s[28][29] = s[29][28] = s[35][36] = s[36][35]
	= s[40][41] = s[41][40] = s[46][47] = s[47][46] = 0;
	
	cin >> n >> k;  // ��Jn, k 
	a[n] = 1;  // n�������i��F���A�]��1 
	
	station (s, a, 0, n, k);
	
	for (int i = 53; i > 0; i--)  // ��a[i] = 1���̤j���A�åO�䬰iMax 
	{
		if(a[i] == 1)
		{
			iMax = i;
			break;
		}
	}
	for (int i = 1; i < iMax; i++)  // ��X 
	{
		if(a[i] == 1)
		{
			cout << i << " ";
		}
	}
	cout << iMax;
	
	return 0;
}

void station(int s[][60], int a[], int x, int staID, int step)
{
	if (step > 0)
	{
		for (int i = 1; i <= 53; i++)  // ��Pn�۾F����(s[n][i] == 1) 
		{
			if (s[staID][i] == 1 && i != x)  // x: �ΥH�M��۾F���ƮɡA���h�W�@�Ӽ�(�W�@�骺staID) 
			{
				a[i] = 1;  // �Y�۾F�A�h�O�Ustation i (�Oa[i] = 1) 
//				cout << i << " " << step << endl;
				station (s, a, staID, i, step-1);  // �O�U���ɪ�staID�A�A��Pi�۾F�����A�ñNstep - 1 
			}
		}	
	}
}
// why step > 0�����for��~ 
