#include <iostream>
#include <cmath>
using namespace std;

void assignASK (int[], int [][7], int[]);

int main()
{
/*	int a[7] = {0}, b[7] = {0}, c[7][7] = {0}, d[7] = {0};
	for (int i = 0; i < 7; i++)
		cin >> a[i];
	for (int i = 0; i < 7; i++)
		cout << a[i] << " ";
	cout << endl;
	assignASK(a, c, d); */

	input

	assignASK ()
	
for i from 0 to 6  // ��ANTS, SVVRL, KMM���t��IEDO���H�Ʀ��� 
	demandDay[i] -= (remainA[i]+remainS[i]+remainK[i])
	if demandDay[i] < 0
		demandDay[i] = 0
	
	���tIEDO�H�� (��Ĥ@�D�ۦP) 
			
	output
			
	return 0;
}

void assignASK(int d[], int dayoff[][7], int remain[])
{
	int demandSum = 0, demand[7] = {0};  // demand: �վ�� 
	int min = d[0], minPos = 0;  // ����demand�̤p�Ȧ�m 
	for (int i = 0; i < 7; i++)
	{
		demandSum += d[i];
		demand[i] = d[i];
		if (d[i] < min)
		{
			min = d[i];
			minPos = i;
		}
	}
	if (demandSum % 5 != 0){
		int r = demandSum % 5;  // �NdemandSum�զ�5������ 
		demand[minPos] += 5 - r;
		demandSum += 5 - r;
		remain[minPos] += 5 - r;  // �N�h�[����������IEDO	
	}

	int fullDay[7] = {0};
	for (int i = 0; i < 7; i++)
	{
		fullDay[i] = demand[i] + demand[(i+2)%7] + demand[(i+4)%7] - (2*demandSum/5);
		if (fullDay[i] > 0)
			dayoff[(i+5)%7][(i+6)%7] += fullDay[i];

		if (fullDay[i] < 0)
			for (int j = i; j < i + 5; j++)
				remain[j%7] += abs(fullDay[i]);
	}
}




