#include <iostream>
using namespace std;

void p1(int [][60], int, int, int, int, int [], int, int [], int[]);  // ―┮竒计程 
void p0(int [][60], int, int, int, int, int [], int, int [], int[]);  // ―锣笲Ω计程 
// p1, p0: 块s[][], x(﹍100), i, j, step, stepMin, tran, tranMin, a[]   

int main()
{
	int start = 0, end = 0, p = 0;  // 块i, j, p 
	int a[60] = {0}, s[60][60] = {0}, stepMin[1] = {53}, tranMin[1] = {6};
	// a: station ID璝itransfer station玥a[i] = 1 
	// s: adjacency matrix // stepMin[0], tranMin[0]: ノㄓstep, transferΩ计程 
	a[4] = a[6] = a[9] = a[14] = a[22] = a[32] = 1;  // 夹癘transfer station 
	for (int i = 1; i < 12; i++)  // 篶adjacency matrix 
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
		if (a[start] == 1)  // 璝癬﹍transfer station块tran-1(癬翴穦砆衡)
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

/* 患癹:
浪琩癬翴(start)琌籔沧翴(end)綟 
璝ぃ綟玥т籔start綟砞伴start
狡Ω璝т籔end綟癹伴挡癘锣笲Ω计籔┮竒计 */

void p1(int s[][60], int x, int start, int end, int step, int stepMin[], int tran, int tranMin[], int a[])
{ // x: 伴start // end: j // step: 竒筁计﹍2 (癬翴, 沧翴) // tran: 锣笲Ω计 
	if(step <= stepMin[0])  // 璝stepゑ程磅︽ㄧΑ 
	{
		if(s[start][end] == 1) // 璝start㎝end綟 
		{
				if (a[start] == 1 && end != x + 2 && end != x - 2 && end != x + 1 && end != x - 1)
					tran++;  // 璝沧翴玡transfer station锣笲Ω计+1 
				if (step < stepMin[0])  // 璝竒筁计ゑ程蠢传程 
				{
					stepMin[0] = step;
					tranMin[0] = tran;	
				}
				else if (tran < tranMin[0])  // 璝step锣笲Ω计耕ぶ蠢传tranMin 
					tranMin[0] = tran;
		}
		else  // ㎝endぃ綟 
		{
			for (int i = 1; i <= 53; i++)  // т籔start綟计(s[start][i] == 1) 
			{
				if (s[start][i] == 1 && i != x)  // i != x: 碝т綟计埃计(伴start)
				{
					if (a[start] == 1 && i != x + 2 && i != x - 2 && i != x + 1 && i != x - 1)
						p1(s, start, i, end, step+1, stepMin, tran+1, tranMin, a);
						// 璝transfer station㊣ㄧΑtran + 1 
					else
						p1(s, start, i, end, step+1, stepMin, tran, tranMin, a);						
				}
			}	
		}
	}
}
void p0(int s[][60], int x, int start, int end, int step, int stepMin[], int tran, int tranMin[], int a[])
{
	if(tran <= tranMin[0] && step <= 53)  // 璝锣笲Ω计ゑ程step <= 53(ぇ程)磅︽ㄧΑ 
	{
		if(s[start][end] == 1)
		{
			if (a[start] == 1 && end != x + 2 && end != x - 2 && end != x + 1 && end != x - 1)
				tran++;  // 璝沧翴玡transfer station锣笲Ω计+1
			if (tran < tranMin[0])  // 璝锣笲Ω计ゑ程蠢传程 
			{
				tranMin[0] = tran;
				stepMin[0] = step;
			}
			else if (step < stepMin[0])  // 璝锣笲Ω计step耕ぶ蠢传stepMin 
				stepMin[0] = step;
		}
		else
		{
			for (int i = 1; i <= 53; i++)  // т籔start綟计(s[start][i] == 1) 
			{
				if (s[start][i] == 1 && i != x)  // i != x: 碝т綟计埃计(伴start) 
				{
					if (a[start] == 1 && i != x + 2 && i != x - 2 && i != x + 1 && i != x - 1)
						p0(s, start, i, end, step+1, stepMin, tran+1, tranMin, a);
						// 璝transfer station㊣ㄧΑtran + 1 						
					else
						p0(s, start, i, end, step+1, stepMin, tran, tranMin, a);						
				}
			}	
		}
	}
}
