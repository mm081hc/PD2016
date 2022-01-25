#include <iostream>
using namespace std;

void swap (int [], int, int);  // swap(): ��J�}�C��m�B�n�洫���y�СA�洫��m 

int main()
{
	int n = 0, p[150] = {0}, s[110][110] = {0}; 
	int order[101] = {0}, min = 0, minFin = 0, indexSum = 0;
	// order: ��e���� // min: setup time�`�M���̤p��
	// minFin: �̲ת�setup time�`�M�̤p�� // indexSum: sum of switching indices
	int pTime = 0, indexMin = 0, iPos = 0, jPos = 0;
	// pTime: sum of processing times // indexMin: ����switching indices�����p���� 
	// iPos, jPos: ����min�ɪ�i, j 
	
	cin >> n;
	for (int i = 1; i <= n; i++)
	{
		order[i] = i;  // ��l����(1, 2,...,n) 
		cin >> p[i];
		pTime += p[i];  // �[�`processing times 
	}
	for (int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			cin >> s[i][j];
	
	for (int i = 1; i < n; i++)
		min += s[order[i]][order[i+1]];  // �p���l��setup time�`�M�A�O�䬰�̤p��min
	minFin = min; // �N��min�]���̲ת��̤p�� 
	
	bool exist = 1;  // exist: ��s�b�̤p�ȮɡA��Ȭ�1 
	while (exist == 1)
	{
		for (int i = 1; i < n; i++)  // �����N��Ƥ��� 
		{
			for (int j = i + 1; j <= n; j++)
			{ 
				swap(order, i, j);  // ��Ƥ��� 
				int sTime = 0;  // sTime: sum of setup time
				for (int k = 1; k < n; k++)
				{
					sTime += s[order[k]][order[k+1]];  // �p���esetup time
					if (sTime > min)  // �Y�w�W�L��e�̤p�ȡA���X�j�� 
						break;
				}
				if (sTime < min || (sTime == min && order[i] + order[j] < indexSum))
				{
					// �Y��esetup time��̤p�Ȥp�A�����̤p��
					// �Y����̤p�ȫh�ˬdswitching indices���M�O�_���p 
					min = sTime;  // ��min, iPos, jPos, indexSum, indexMin 
					iPos = i;
					jPos = j;
					indexSum = order[i] + order[j];
					if (order[i] < order[j])  // �N���p��switching indices�ȿ�JindexMin 
						indexMin = order[i];
					else
						indexMin = order[j];
				}
				else if (sTime == min && order[i] + order[j] == indexSum
						&& (order[i] < indexMin || order[j] < indexMin))
				{
					// �Y��esetup time����min�A�BindexSum�ۦP�A
					// �h�ˬdswitching indices���@�O�_��indexMin�p�A�Y���h����indices
					min = sTime;
					iPos = i;
					jPos = j;
					indexSum = order[i] + order[j];					
					if (order[i] < order[j])
						indexMin = order[i];
					else
						indexMin = order[j];	
				}
				swap (order, i, j);  // ��ƴ��^���m
			}
		}
		if (minFin == min)  // �Y������̲׳̤p�Ȥ������ܡA�Nexist�]��0�A���X�j��
			exist = 0;
		else  // �YminFin���ܡA���ܥثemin�ɪ����A�A�æA���ˬd�O�_����p�� 
		{
			exist = 1;
			minFin = min;
			swap(order, iPos, jPos); 
		}
	}
	
	for (int i = 1; i <= n; i++)
		cout << order[i] << " ";
	cout << pTime + minFin;  // ��Xprocessing time + setup time
	
	return 0;
}

void swap (int x[], int a, int b)
{
	int temp = 0;
	temp = x[a];
	x[a] = x[b];
	x[b] = temp;
}
