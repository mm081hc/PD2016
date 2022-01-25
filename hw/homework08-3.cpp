#include <iostream>
using namespace std;

int main ()
{
	int d[7] = {0}, dMemo[7] = {0}, schedule[7] = {0};
	// d: ��J��demands // dMemo: �Pd�ۦP�A�Ψ��٭�d // schedule: �һ�ĵ���
	for (int i = 0; i < 7; i++)  // ��J
	{
		cin >> d[i];
		dMemo[i] = d[i];
	}
		
	for (int i = 0; i < 7; i++)
	{
		for (int k = 0; k < 7; k++)
		{
			int day = i + k;  // �q��i+1�Ѷ}�l 
			if (i + k > 6)
				day = i + k - 7;  // �}�C��m��0~6�A�Yi+k > 6�A�h�q0�}�l��_ 
			if (d[day] > 0)
			{
				int policeNum = d[day];  // policeNum: ���tĵ���d[k]
				for (int j = 0; j < 5; j++)   // �qd[]�����Ҥ��t��ĵ���(policeNum) 
				{ 
					if (day + j > 6)  // �}�C��m��0~6�A�Yday+j > 6�A�h�q0�}�l��_  
						d[day+j-7] -= policeNum;
					else
						d[day+j] -= policeNum;
				}
				schedule[i] += policeNum;  // �O�U�C�Ѥ��t��ĵ���
			}
		}
		for (int k = 0; k < 7; k++)  // �٭�d�}�C������
			d[k] = dMemo[k];
	}

	for (int i = 0; i < 6; i++)
		cout << schedule[i] << " ";
	cout << schedule[6];

	return 0;
}
