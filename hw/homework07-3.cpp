#include <iostream>
using namespace std;

void p1(int [][60], int, int, int, int, int [], int, int [], int[]);  // �D�Ҹg���Ƴ̤p�� 
void p0(int [][60], int, int, int, int, int [], int, int [], int[]);  // �D��B���Ƴ̤p�� 
// p1, p0: ��Js[][], x(��l�Ȭ�100), i, j, step, stepMin, tran, tranMin, a[]   

int main()
{
	int start = 0, end = 0, p = 0;  // ��J��i, j, p 
	int a[60] = {0}, s[60][60] = {0}, stepMin[1] = {53}, tranMin[1] = {6};
	// a: station ID�A�Yi��transfer station�A�ha[i] = 1 
	// s: adjacency matrix // stepMin[0], tranMin[0]: �ΨӦs��step, transfer���ƪ��̤p�� 
	a[4] = a[6] = a[9] = a[14] = a[22] = a[32] = 1;  // �аOtransfer station 
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
	
	cin >> start >> end >> p;
	if (p == 1) 
	{
		if (a[start] == 1)  // �Y�_�l����transfer station�A��Jtran��-1(�]���_�I�]�|�Q��J)
			p1(s, 100, start, end, 2, stepMin, -1, tranMin, a);			
		else
			p1(s, 100, start, end, 2, stepMin, 0, tranMin, a);
	}
	else
	{
		if (a[start] == 1)
			p0(s, 100, start, end, 2, stepMin, -1, tranMin, a);			
		else
			p0(s, 100, start, end, 2, stepMin, 0, tranMin, a);	
	}
	
	cout << tranMin[0] << " " << stepMin[0];
	return 0;
}

/* ���j:
�ˬd�_�I(start)�O�_�P���I(end)�۾F�A 
�Y���۾F�A�h��Pstart�۾F�����A�]���U�@�骺start�A
���Ʀh����Y���Pend�۾F�����A�j�鵲���A�O�U��B���ƻP�Ҹg���� */

void p1(int s[][60], int x, int start, int end, int step, int stepMin[], int tran, int tranMin[], int a[])
{ // x: �W�@�骺start // end: j // step: �w�g�L���ơA��l�Ȭ�2 (�]�t�_�I, ���I) // tran: ��B���� 
	if(step <= stepMin[0])  // �Ystep��̤p�Ȥp�A����禡 
	{
		if(s[start][end] == 1) // �Ystart�Mend�۾F 
		{
				if (a[start] == 1 && end != x + 2 && end != x - 2 && end != x + 1 && end != x - 1)
					tran++;  // �Y���I�e�@����transfer station�A��B����+1 
				if (step < stepMin[0])  // �Y�w�g�L���Ƥ�̤p�Ȥp�A�����̤p�� 
				{
					stepMin[0] = step;
					tranMin[0] = tran;	
				}
				else if (tran < tranMin[0])  // �Ystep�ۦP����B���Ƹ��֡A����tranMin 
					tranMin[0] = tran;
		}
		else  // �Mend���۾F 
		{
			for (int i = 1; i <= 53; i++)  // ��Pstart�۾F����(s[start][i] == 1) 
			{
				if (s[start][i] == 1 && i != x)  // i != x: �M��۾F���ƮɡA���h�W�@�Ӽ�(�W�@�骺start)
				{
					if (a[start] == 1 && i != x + 2 && i != x - 2 && i != x + 1 && i != x - 1)
						p1(s, start, i, end, step+1, stepMin, tran+1, tranMin, a);
						// �Y������transfer station�A�I�s�禡��tran + 1 
					else
						p1(s, start, i, end, step+1, stepMin, tran, tranMin, a);						
				}
			}	
		}
	}
}
void p0(int s[][60], int x, int start, int end, int step, int stepMin[], int tran, int tranMin[], int a[])
{
	if(tran <= tranMin[0] && step <= 53)  // �Y��B���Ƥ�̤p�Ȥp�A�Bstep <= 53(�i�ध�̤j��)�A����禡 
	{
		if(s[start][end] == 1)
		{
			if (a[start] == 1 && end != x + 2 && end != x - 2 && end != x + 1 && end != x - 1)
				tran++;  // �Y���I�e�@����transfer station�A��B����+1
			if (tran < tranMin[0])  // �Y��B���Ƥ�̤p�Ȥp�A�����̤p�� 
			{
				tranMin[0] = tran;
				stepMin[0] = step;
			}
			else if (step < stepMin[0])  // �Y��B���ƬۦP��step���֡A����stepMin 
				stepMin[0] = step;
		}
		else
		{
			for (int i = 1; i <= 53; i++)  // ��Pstart�۾F����(s[start][i] == 1) 
			{
				if (s[start][i] == 1 && i != x)  // i != x: �M��۾F���ƮɡA���h�W�@�Ӽ�(�W�@�骺start) 
				{
					if (a[start] == 1 && i != x + 2 && i != x - 2 && i != x + 1 && i != x - 1)
						p0(s, start, i, end, step+1, stepMin, tran+1, tranMin, a);
						// �Y������transfer station�A�I�s�禡��tran + 1 						
					else
						p0(s, start, i, end, step+1, stepMin, tran, tranMin, a);						
				}
			}	
		}
	}
}
