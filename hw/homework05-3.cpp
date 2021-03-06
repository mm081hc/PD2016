#include <iostream>
using namespace std;

void swap (int [], int, int);  // swap(): 块皚竚璶ユ传畒夹ユ传竚 

int main()
{
	int n = 0, p[150] = {0}, s[110][110] = {0}; 
	int order[101] = {0}, min = 0, minFin = 0, indexSum = 0;
	// order: 讽玡抖 // min: setup time羆㎝ぇ程
	// minFin: 程沧setup time羆㎝程 // indexSum: sum of switching indices
	int pTime = 0, indexMin = 0, iPos = 0, jPos = 0;
	// pTime: sum of processing times // indexMin: 魁switching indicesい耕计 
	// iPos, jPos: 魁mini, j 
	
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		order[i] = i;  // ﹍抖(1, 2,...,n) 
		cin >> p[i];
		pTime += p[i];  // 羆processing times 
	}
	for (int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			cin >> s[i][j];
	
	for (int i = 1; i < n; i++)
		min += s[order[i]][order[i+1]];  // 璸衡﹍setup time羆㎝ㄤ程min
	minFin = min; // 盢min砞程沧程 
	
	bool exist = 1;  // exist: 讽程ㄤ1 
	while (exist == 1)
	{
		for (int i = 1; i < n; i++)  // ヴ種ㄢ计が传 
		{
			for (int j = i + 1; j <= n; j++)
			{ 
				swap(order, i, j);  // ㄢ计が传 
				int sTime = 0;  // sTime: sum of setup time
				for (int k = 1; k < n; k++)
				{
					sTime += s[order[k]][order[k+1]];  // 璸衡讽玡setup time
					if (sTime > min)  // 璝禬筁讽玡程铬癹伴 
						break;
				}
				if (sTime < min || (sTime == min && order[i] + order[j] < indexSum))
				{
					// 璝讽玡setup timeゑ程蠢传程
					// 璝单程玥浪琩switching indices㎝琌耕 
					min = sTime;  // 传min, iPos, jPos, indexSum, indexMin 
					iPos = i;
					jPos = j;
					indexSum = order[i] + order[j];
					if (order[i] < order[j])  // 盢耕switching indices块indexMin 
						indexMin = order[i];
					else
						indexMin = order[j];
				}
				else if (sTime == min && order[i] + order[j] == indexSum
						&& (order[i] < indexMin || order[j] < indexMin))
				{
					// 璝讽玡setup time单minindexSum
					// 玥浪琩switching indicesヴ琌ゑindexMin璝Τ玥蠢传indices
					min = sTime;
					iPos = i;
					jPos = j;
					indexSum = order[i] + order[j];					
					if (order[i] < order[j])
						indexMin = order[i];
					else
						indexMin = order[j];	
				}
				swap (order, i, j);  // ㄢ计传竚
			}
		}
		if (minFin == min)  // 璝が传程沧程ごゼэ跑盢exist砞0铬癹伴
			exist = 0;
		else  // 璝minFinэ跑传ヘ玡min篈Ω浪琩琌Τ 
		{
			exist = 1;
			minFin = min;
			swap(order, iPos, jPos); 
		}
	}
	
	for (int i = 1; i <= n; i++)
		cout << order[i] << " ";
	cout << pTime + minFin;  // 块processing time + setup time
	
	return 0;
}

void swap (int x[], int a, int b)
{
	int temp = 0;
	temp = x[a];
	x[a] = x[b];
	x[b] = temp;
}
