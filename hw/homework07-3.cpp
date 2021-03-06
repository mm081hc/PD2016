#include <iostream>
using namespace std;

void p1(int [][60], int, int, int, int, int [], int, int [], int[]);  // 求所經站數最小值 
void p0(int [][60], int, int, int, int, int [], int, int [], int[]);  // 求轉運次數最小值 
// p1, p0: 輸入s[][], x(初始值為100), i, j, step, stepMin, tran, tranMin, a[]   

int main()
{
	int start = 0, end = 0, p = 0;  // 輸入的i, j, p 
	int a[60] = {0}, s[60][60] = {0}, stepMin[1] = {53}, tranMin[1] = {6};
	// a: station ID，若i為transfer station，則a[i] = 1 
	// s: adjacency matrix // stepMin[0], tranMin[0]: 用來存取step, transfer次數的最小值 
	a[4] = a[6] = a[9] = a[14] = a[22] = a[32] = 1;  // 標記transfer station 
	for (int i = 1; i < 12; i++)  // 建構adjacency matrix 
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
		if (a[start] == 1)  // 若起始站為transfer station，輸入tran為-1(因為起點也會被算入)
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

/* 遞迴:
檢查起點(start)是否與終點(end)相鄰， 
若不相鄰，則找與start相鄰的站，設為下一圈的start，
重複多次後若找到與end相鄰的站，迴圈結束，記下轉運次數與所經站數 */

void p1(int s[][60], int x, int start, int end, int step, int stepMin[], int tran, int tranMin[], int a[])
{ // x: 上一圈的start // end: j // step: 已經過站數，初始值為2 (包含起點, 終點) // tran: 轉運次數 
	if(step <= stepMin[0])  // 若step比最小值小，執行函式 
	{
		if(s[start][end] == 1) // 若start和end相鄰 
		{
				if (a[start] == 1 && end != x + 2 && end != x - 2 && end != x + 1 && end != x - 1)
					tran++;  // 若終點前一站為transfer station，轉運次數+1 
				if (step < stepMin[0])  // 若已經過站數比最小值小，替換最小值 
				{
					stepMin[0] = step;
					tranMin[0] = tran;	
				}
				else if (tran < tranMin[0])  // 若step相同但轉運次數較少，替換tranMin 
					tranMin[0] = tran;
		}
		else  // 和end不相鄰 
		{
			for (int i = 1; i <= 53; i++)  // 找與start相鄰的數(s[start][i] == 1) 
			{
				if (s[start][i] == 1 && i != x)  // i != x: 尋找相鄰的數時，除去上一個數(上一圈的start)
				{
					if (a[start] == 1 && i != x + 2 && i != x - 2 && i != x + 1 && i != x - 1)
						p1(s, start, i, end, step+1, stepMin, tran+1, tranMin, a);
						// 若此站為transfer station，呼叫函式時tran + 1 
					else
						p1(s, start, i, end, step+1, stepMin, tran, tranMin, a);						
				}
			}	
		}
	}
}
void p0(int s[][60], int x, int start, int end, int step, int stepMin[], int tran, int tranMin[], int a[])
{
	if(tran <= tranMin[0] && step <= 53)  // 若轉運次數比最小值小，且step <= 53(可能之最大值)，執行函式 
	{
		if(s[start][end] == 1)
		{
			if (a[start] == 1 && end != x + 2 && end != x - 2 && end != x + 1 && end != x - 1)
				tran++;  // 若終點前一站為transfer station，轉運次數+1
			if (tran < tranMin[0])  // 若轉運次數比最小值小，替換最小值 
			{
				tranMin[0] = tran;
				stepMin[0] = step;
			}
			else if (step < stepMin[0])  // 若轉運次數相同但step較少，替換stepMin 
				stepMin[0] = step;
		}
		else
		{
			for (int i = 1; i <= 53; i++)  // 找與start相鄰的數(s[start][i] == 1) 
			{
				if (s[start][i] == 1 && i != x)  // i != x: 尋找相鄰的數時，除去上一個數(上一圈的start) 
				{
					if (a[start] == 1 && i != x + 2 && i != x - 2 && i != x + 1 && i != x - 1)
						p0(s, start, i, end, step+1, stepMin, tran+1, tranMin, a);
						// 若此站為transfer station，呼叫函式時tran + 1 						
					else
						p0(s, start, i, end, step+1, stepMin, tran, tranMin, a);						
				}
			}	
		}
	}
}
